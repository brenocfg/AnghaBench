#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_input_src_internal {size_t cmd_buffer; size_t cmd_buffer_size; int drop; } ;
struct mp_input_src {int /*<<< orphan*/  input_ctx; int /*<<< orphan*/  log; struct mp_input_src_internal* in; } ;
struct mp_cmd {int dummy; } ;
struct TYPE_5__ {size_t member_0; size_t member_1; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 size_t CMD_BUFFER ; 
 int /*<<< orphan*/  MP_WARN (struct mp_input_src*,char*) ; 
 TYPE_1__ bstr_strip (TYPE_1__) ; 
 char* memchr (char*,char,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t,char*,size_t) ; 
 struct mp_cmd* mp_input_parse_cmd_str (int /*<<< orphan*/ ,TYPE_1__,char*) ; 
 int /*<<< orphan*/  mp_input_queue_cmd (int /*<<< orphan*/ ,struct mp_cmd*) ; 
 size_t talloc_size (struct mp_input_src_internal*,size_t) ; 

void mp_input_src_feed_cmd_text(struct mp_input_src *src, char *buf, size_t len)
{
    struct mp_input_src_internal *in = src->in;
    if (!in->cmd_buffer)
        in->cmd_buffer = talloc_size(in, CMD_BUFFER);
    while (len) {
        char *next = memchr(buf, '\n', len);
        bool term = !!next;
        next = next ? next + 1 : buf + len;
        size_t copy = next - buf;
        bool overflow = copy > CMD_BUFFER - in->cmd_buffer_size;
        if (overflow || in->drop) {
            in->cmd_buffer_size = 0;
            in->drop = overflow || !term;
            MP_WARN(src, "Dropping overlong line.\n");
        } else {
            memcpy(in->cmd_buffer + in->cmd_buffer_size, buf, copy);
            in->cmd_buffer_size += copy;
            buf += copy;
            len -= copy;
            if (term) {
                bstr s = {in->cmd_buffer, in->cmd_buffer_size};
                s = bstr_strip(s);
                struct mp_cmd *cmd = mp_input_parse_cmd_str(src->log, s, "<>");
                if (cmd)
                    mp_input_queue_cmd(src->input_ctx, cmd);
                in->cmd_buffer_size = 0;
            }
        }
    }
}