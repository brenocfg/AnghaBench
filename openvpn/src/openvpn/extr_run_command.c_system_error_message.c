#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gc_arena {int dummy; } ;
struct buffer {scalar_t__ data; } ;

/* Variables and functions */
#define  OPENVPN_EXECVE_ERROR 129 
 int const OPENVPN_EXECVE_FAILURE ; 
#define  OPENVPN_EXECVE_NOT_ALLOWED 128 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 

__attribute__((used)) static const char *
system_error_message(int stat, struct gc_arena *gc)
{
    struct buffer out = alloc_buf_gc(256, gc);

    switch (stat)
    {
        case OPENVPN_EXECVE_NOT_ALLOWED:
            buf_printf(&out, "disallowed by script-security setting");
            break;

#ifdef _WIN32
        case OPENVPN_EXECVE_ERROR:
            buf_printf(&out, "external program did not execute -- ");
        /* fall through */

        default:
            buf_printf(&out, "returned error code %d", stat);
            break;
#else  /* ifdef _WIN32 */

        case OPENVPN_EXECVE_ERROR:
            buf_printf(&out, "external program fork failed");
            break;

        default:
            if (!WIFEXITED(stat))
            {
                buf_printf(&out, "external program did not exit normally");
            }
            else
            {
                const int cmd_ret = WEXITSTATUS(stat);
                if (!cmd_ret)
                {
                    buf_printf(&out, "external program exited normally");
                }
                else if (cmd_ret == OPENVPN_EXECVE_FAILURE)
                {
                    buf_printf(&out, "could not execute external program");
                }
                else
                {
                    buf_printf(&out, "external program exited with error status: %d", cmd_ret);
                }
            }
            break;
#endif /* ifdef _WIN32 */
    }
    return (const char *)out.data;
}