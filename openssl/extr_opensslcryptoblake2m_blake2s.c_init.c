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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BLAKE2S_PARAM ;

/* Variables and functions */
 int BLAKE2s_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_md_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blake2s_param_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init(EVP_MD_CTX *ctx)
{
    BLAKE2S_PARAM P;
    blake2s_param_init(&P);
    return BLAKE2s_Init(EVP_MD_CTX_md_data(ctx), &P);
}