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
struct TYPE_3__ {int* state; scalar_t__ idx2; scalar_t__ idx1; } ;
typedef  int HPDF_UINT ;
typedef  int HPDF_BYTE ;
typedef  TYPE_1__ HPDF_ARC4_Ctx_Rec ;

/* Variables and functions */
 int HPDF_ARC4_BUF_SIZE ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
ARC4Init  (HPDF_ARC4_Ctx_Rec  *ctx,
                        const HPDF_BYTE    *key,
                        HPDF_UINT          key_len)
{
    HPDF_BYTE tmp_array[HPDF_ARC4_BUF_SIZE];
    HPDF_UINT i;
    HPDF_UINT j = 0;

    HPDF_PTRACE((" ARC4Init\n"));

    for (i = 0; i < HPDF_ARC4_BUF_SIZE; i++)
        ctx->state[i] = (HPDF_BYTE)i;

    for (i = 0; i < HPDF_ARC4_BUF_SIZE; i++)
        tmp_array[i] = key[i % key_len];

    for (i = 0; i < HPDF_ARC4_BUF_SIZE; i++) {
        HPDF_BYTE tmp;

        j = (j + ctx->state[i] + tmp_array[i]) % HPDF_ARC4_BUF_SIZE;

        tmp = ctx->state[i];
        ctx->state[i] = ctx->state[j];
        ctx->state[j] = tmp;
    }

    ctx->idx1 = 0;
    ctx->idx2 = 0;
}