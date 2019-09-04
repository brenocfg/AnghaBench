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
struct bwriter_shader {int dummy; } ;
typedef  enum shader_type { ____Placeholder_shader_type } shader_type ;
typedef  int /*<<< orphan*/  YY_BUFFER_STATE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  hlsl__delete_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlsl__scan_string (char const*) ; 
 int /*<<< orphan*/  hlsl__switch_to_buffer (int /*<<< orphan*/ ) ; 
 struct bwriter_shader* parse_hlsl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char**) ; 

struct bwriter_shader *parse_hlsl_shader(const char *text, enum shader_type type, DWORD major, DWORD minor,
        const char *entrypoint, char **messages)
{
    struct bwriter_shader *ret = NULL;
    YY_BUFFER_STATE buffer;

    buffer = hlsl__scan_string(text);
    hlsl__switch_to_buffer(buffer);

    ret = parse_hlsl(type, major, minor, entrypoint, messages);

    hlsl__delete_buffer(buffer);
    return ret;
}