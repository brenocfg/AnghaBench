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

/* Variables and functions */
 int /*<<< orphan*/  BWRITERDECLUSAGE_COLOR ; 
 int /*<<< orphan*/  BWRITERDECLUSAGE_FOG ; 
 int /*<<< orphan*/  BWRITERDECLUSAGE_POSITION ; 
 int /*<<< orphan*/  BWRITERDECLUSAGE_PSIZE ; 
 int /*<<< orphan*/  BWRITERDECLUSAGE_TEXCOORD ; 
 int /*<<< orphan*/  BWRITERSP_WRITEMASK_ALL ; 
 int /*<<< orphan*/  OD0_REG ; 
 int /*<<< orphan*/  OD1_REG ; 
 int /*<<< orphan*/  OFOG_REG ; 
 int /*<<< orphan*/  OFOG_WRITEMASK ; 
 int /*<<< orphan*/  OPOS_REG ; 
 int /*<<< orphan*/  OPTS_REG ; 
 int /*<<< orphan*/  OPTS_WRITEMASK ; 
 int /*<<< orphan*/  OT0_REG ; 
 int /*<<< orphan*/  OT1_REG ; 
 int /*<<< orphan*/  OT2_REG ; 
 int /*<<< orphan*/  OT3_REG ; 
 int /*<<< orphan*/  OT4_REG ; 
 int /*<<< orphan*/  OT5_REG ; 
 int /*<<< orphan*/  OT6_REG ; 
 int /*<<< orphan*/  OT7_REG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  record_declaration (struct bwriter_shader*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen_oldvs_output(struct bwriter_shader *shader) {
    record_declaration(shader, BWRITERDECLUSAGE_POSITION, 0, 0, TRUE, OPOS_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 0, 0, TRUE, OT0_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 1, 0, TRUE, OT1_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 2, 0, TRUE, OT2_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 3, 0, TRUE, OT3_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 4, 0, TRUE, OT4_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 5, 0, TRUE, OT5_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 6, 0, TRUE, OT6_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 7, 0, TRUE, OT7_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_FOG, 0, 0, TRUE, OFOG_REG, OFOG_WRITEMASK, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_PSIZE, 0, 0, TRUE, OPTS_REG, OPTS_WRITEMASK, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_COLOR, 0, 0, TRUE, OD0_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_COLOR, 1, 0, TRUE, OD1_REG, BWRITERSP_WRITEMASK_ALL, TRUE);
}