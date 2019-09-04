#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  m_profile_t ;
struct TYPE_32__ {scalar_t__ recursion_depth; } ;
typedef  TYPE_1__ m_config_t ;
typedef  int /*<<< orphan*/  loc ;
struct TYPE_33__ {long long len; char* start; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (TYPE_2__) ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,char const*,...) ; 
 TYPE_2__ bstr_cut (TYPE_2__,long long) ; 
 scalar_t__ bstr_eatstart0 (TYPE_2__*,char*) ; 
 scalar_t__ bstr_equals0 (TYPE_2__,char*) ; 
 int /*<<< orphan*/  bstr_getline (TYPE_2__,TYPE_2__*) ; 
 TYPE_2__ bstr_splice (TYPE_2__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bstr_split_tok (TYPE_2__,char*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__ bstr_strip (TYPE_2__) ; 
 TYPE_2__ bstr_strip_linebreaks (int /*<<< orphan*/ ) ; 
 int bstrchr (TYPE_2__,char) ; 
 char* bstrto0 (void*,TYPE_2__) ; 
 long long bstrtoll (TYPE_2__,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * m_config_add_profile (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  m_config_finish_default_profile (TYPE_1__*,int) ; 
 int m_config_set_profile_option (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/  m_profile_set_desc (int /*<<< orphan*/ *,TYPE_2__) ; 
 scalar_t__ mp_isalnum (char) ; 
 scalar_t__ skip_ws (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 int /*<<< orphan*/  talloc_free_children (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

int m_config_parse(m_config_t *config, const char *location, bstr data,
                   char *initial_section, int flags)
{
    m_profile_t *profile = m_config_add_profile(config, initial_section);
    void *tmp = talloc_new(NULL);
    int line_no = 0;
    int errors = 0;

    bstr_eatstart0(&data, "\xEF\xBB\xBF"); // skip BOM

    while (data.len) {
        talloc_free_children(tmp);
        bool ok = false;

        line_no++;
        char loc[512];
        snprintf(loc, sizeof(loc), "%s:%d:", location, line_no);

        bstr line = bstr_strip_linebreaks(bstr_getline(data, &data));
        if (!skip_ws(&line))
            continue;

        // Profile declaration
        if (bstr_eatstart0(&line, "[")) {
            bstr profilename;
            if (!bstr_split_tok(line, "]", &profilename, &line)) {
                MP_ERR(config, "%s missing closing ]\n", loc);
                goto error;
            }
            if (skip_ws(&line)) {
                MP_ERR(config, "%s unparseable extra characters: '%.*s'\n",
                       loc, BSTR_P(line));
                goto error;
            }
            profile = m_config_add_profile(config, bstrto0(tmp, profilename));
            continue;
        }

        bstr_eatstart0(&line, "--");

        bstr option = line;
        while (line.len && (mp_isalnum(line.start[0]) || line.start[0] == '_' ||
                            line.start[0] == '-'))
            line = bstr_cut(line, 1);
        option.len = option.len - line.len;
        skip_ws(&line);

        bstr value = {0};
        if (bstr_eatstart0(&line, "=")) {
            skip_ws(&line);
            if (line.len && (line.start[0] == '"' || line.start[0] == '\'')) {
                // Simple quoting, like "value"
                char term[2] = {line.start[0], 0};
                line = bstr_cut(line, 1);
                if (!bstr_split_tok(line, term, &value, &line)) {
                    MP_ERR(config, "%s unterminated quote\n", loc);
                    goto error;
                }
            } else if (bstr_eatstart0(&line, "%")) {
                // Quoting with length, like %5%value
                bstr rest;
                long long len = bstrtoll(line, &rest, 10);
                if (rest.len == line.len || !bstr_eatstart0(&rest, "%") ||
                    len > rest.len)
                {
                    MP_ERR(config, "%s fixed-length quoting expected - put "
                           "\"quotes\" around the option value if you did not "
                           "intend to use this, but your option value starts "
                           "with '%%'\n", loc);
                    goto error;
                }
                value = bstr_splice(rest, 0, len);
                line = bstr_cut(rest, len);
            } else {
                // No quoting; take everything until the comment or end of line
                int end = bstrchr(line, '#');
                value = bstr_strip(end < 0 ? line : bstr_splice(line, 0, end));
                line.len = 0;
            }
        }
        if (skip_ws(&line)) {
            MP_ERR(config, "%s unparseable extra characters: '%.*s'\n",
                   loc, BSTR_P(line));
            goto error;
        }

        int res;
        if (bstr_equals0(option, "profile-desc")) {
            m_profile_set_desc(profile, value);
            res = 0;
        } else {
            res = m_config_set_profile_option(config, profile, option, value);
        }
        if (res < 0) {
            MP_ERR(config, "%s setting option %.*s='%.*s' failed.\n",
                   loc, BSTR_P(option), BSTR_P(value));
            goto error;
        }

        ok = true;
    error:
        if (!ok)
            errors++;
        if (errors > 16) {
            MP_ERR(config, "%s: too many errors, stopping.\n", location);
            break;
        }
    }

    if (config->recursion_depth == 0)
        m_config_finish_default_profile(config, flags);

    talloc_free(tmp);
    return 1;
}