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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BWRITERDECLUSAGE_COLOR ; 
 int /*<<< orphan*/  BWRITERDECLUSAGE_TEXCOORD ; 
 int /*<<< orphan*/  BWRITERSP_WRITEMASK_ALL ; 
 int /*<<< orphan*/  C0_VARYING ; 
 int /*<<< orphan*/  C1_VARYING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  T0_VARYING ; 
 int /*<<< orphan*/  T1_VARYING ; 
 int /*<<< orphan*/  T2_VARYING ; 
 int /*<<< orphan*/  T3_VARYING ; 
 int /*<<< orphan*/  T4_VARYING ; 
 int /*<<< orphan*/  T5_VARYING ; 
 int /*<<< orphan*/  T6_VARYING ; 
 int /*<<< orphan*/  T7_VARYING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  record_declaration (struct bwriter_shader*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen_oldps_input(struct bwriter_shader *shader, DWORD texcoords) {
    switch(texcoords) {
        case 8: record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 7, 0, FALSE, T7_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
            /* fall through */
        case 7: record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 6, 0, FALSE, T6_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
            /* fall through */
        case 6: record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 5, 0, FALSE, T5_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
            /* fall through */
        case 5: record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 4, 0, FALSE, T4_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
            /* fall through */
        case 4: record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 3, 0, FALSE, T3_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
            /* fall through */
        case 3: record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 2, 0, FALSE, T2_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
            /* fall through */
        case 2: record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 1, 0, FALSE, T1_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
            /* fall through */
        case 1: record_declaration(shader, BWRITERDECLUSAGE_TEXCOORD, 0, 0, FALSE, T0_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
    };
    record_declaration(shader, BWRITERDECLUSAGE_COLOR, 0, 0, FALSE, C0_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
    record_declaration(shader, BWRITERDECLUSAGE_COLOR, 1, 0, FALSE, C1_VARYING, BWRITERSP_WRITEMASK_ALL, TRUE);
}