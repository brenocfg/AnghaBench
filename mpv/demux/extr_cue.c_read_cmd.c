#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bstr {scalar_t__ len; int /*<<< orphan*/ * start; } ;
typedef  enum cue_command { ____Placeholder_cue_command } cue_command ;
struct TYPE_2__ {int command; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int CUE_EMPTY ; 
 int CUE_ERROR ; 
 int /*<<< orphan*/  WHITESPACE ; 
 struct bstr bstr0 (int /*<<< orphan*/ ) ; 
 scalar_t__ bstr_case_startswith (struct bstr,struct bstr) ; 
 struct bstr bstr_cut (struct bstr,scalar_t__) ; 
 int /*<<< orphan*/  bstr_getline (struct bstr,struct bstr*) ; 
 struct bstr bstr_lstrip (struct bstr) ; 
 struct bstr bstr_strip_linebreaks (int /*<<< orphan*/ ) ; 
 TYPE_1__* cue_command_strings ; 
 int /*<<< orphan*/  strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum cue_command read_cmd(struct bstr *data, struct bstr *out_params)
{
    struct bstr line = bstr_strip_linebreaks(bstr_getline(*data, data));
    line = bstr_lstrip(line);
    if (line.len == 0)
        return CUE_EMPTY;
    for (int n = 0; cue_command_strings[n].command != -1; n++) {
        struct bstr name = bstr0(cue_command_strings[n].text);
        if (bstr_case_startswith(line, name)) {
            struct bstr rest = bstr_cut(line, name.len);
            if (rest.len && !strchr(WHITESPACE, rest.start[0]))
                continue;
            if (out_params)
                *out_params = bstr_lstrip(rest);
            return cue_command_strings[n].command;
        }
    }
    return CUE_ERROR;
}