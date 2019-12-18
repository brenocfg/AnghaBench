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
typedef  int /*<<< orphan*/  YY_BUFFER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,char const*,char**) ; 
 int /*<<< orphan*/  asmshader__delete_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asmshader__scan_string (char const*) ; 
 int /*<<< orphan*/  asmshader__switch_to_buffer (int /*<<< orphan*/ ) ; 
 struct bwriter_shader* parse_asm_shader (char**) ; 

struct bwriter_shader *SlAssembleShader(const char *text, char **messages) {
    struct bwriter_shader *ret = NULL;
    YY_BUFFER_STATE buffer;
    TRACE("%p, %p\n", text, messages);

    buffer = asmshader__scan_string(text);
    asmshader__switch_to_buffer(buffer);

    ret = parse_asm_shader(messages);

    asmshader__delete_buffer(buffer);

    return ret;
}