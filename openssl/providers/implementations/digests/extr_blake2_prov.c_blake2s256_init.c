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
typedef  int /*<<< orphan*/  BLAKE2S_PARAM ;
typedef  int /*<<< orphan*/  BLAKE2S_CTX ;

/* Variables and functions */
 int blake2s_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blake2s_param_init (int /*<<< orphan*/ *) ; 

int blake2s256_init(void *ctx)
{
    BLAKE2S_PARAM P;

    blake2s_param_init(&P);
    return blake2s_init((BLAKE2S_CTX *)ctx, &P);
}