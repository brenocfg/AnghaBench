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
struct shader_reg {int dummy; } ;
struct asm_parser {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  asmparser_texhelper (struct asm_parser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct shader_reg const*,struct shader_reg*) ; 
 struct shader_reg map_oldps_register (struct shader_reg const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asmparser_tex(struct asm_parser *This, DWORD mod, DWORD shift,
                          const struct shader_reg *dst) {
    struct shader_reg src;

    /* The first source register is the varying containing the coordinate */
    src = map_oldps_register(dst, TRUE);
    asmparser_texhelper(This, mod, shift, dst, &src);
}