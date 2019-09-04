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
struct TYPE_2__ {int swizzle; } ;
struct shader_reg {TYPE_1__ u; } ;
struct asm_parser {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int BWRITERVS_W_X ; 
 int BWRITERVS_X_W ; 
 int BWRITERVS_Y_X ; 
 int BWRITERVS_Z_X ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  asmparser_texhelper (struct asm_parser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct shader_reg const*,struct shader_reg*) ; 
 struct shader_reg map_oldps_register (struct shader_reg const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asmparser_texreg2ar(struct asm_parser *This, DWORD mod, DWORD shift,
                                const struct shader_reg *dst,
                                const struct shader_reg *src0) {
    struct shader_reg src;

    src = map_oldps_register(src0, FALSE);
    /* Supply the correct swizzle */
    src.u.swizzle = BWRITERVS_X_W | BWRITERVS_Y_X | BWRITERVS_Z_X | BWRITERVS_W_X;
    asmparser_texhelper(This, mod, shift, dst, &src);
}