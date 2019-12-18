#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demuxer {TYPE_1__* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ lavf_priv_t ;
typedef  int /*<<< orphan*/  bstr ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demuxer*,char*,char*) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 scalar_t__ bstr_split_tok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matches_avinputformat_name (TYPE_1__*,char*) ; 
 scalar_t__ mp_is_url (int /*<<< orphan*/ ) ; 
 char* replace_idx_ext (void*,int /*<<< orphan*/ ) ; 
 char* talloc_asprintf (void*,char*,char*,...) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void guess_and_set_vobsub_name(struct demuxer *demuxer, AVDictionary **d)
{
    lavf_priv_t *priv = demuxer->priv;
    if (!matches_avinputformat_name(priv, "vobsub"))
        return;

    void *tmp = talloc_new(NULL);
    bstr bfilename = bstr0(priv->filename);
    char *subname = NULL;
    if (mp_is_url(bfilename)) {
        // It might be a http URL, which has additional parameters after the
        // end of the actual file path.
        bstr start, end;
        if (bstr_split_tok(bfilename, "?", &start, &end)) {
            subname = replace_idx_ext(tmp, start);
            if (subname)
                subname = talloc_asprintf(tmp, "%s?%.*s", subname, BSTR_P(end));
        }
    }
    if (!subname)
        subname = replace_idx_ext(tmp, bfilename);
    if (!subname)
        subname = talloc_asprintf(tmp, "%.*s.sub", BSTR_P(bfilename));

    MP_VERBOSE(demuxer, "Assuming associated .sub file: %s\n", subname);
    av_dict_set(d, "sub_name", subname, 0);
    talloc_free(tmp);
}