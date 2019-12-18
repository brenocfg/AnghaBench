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
typedef  int /*<<< orphan*/  HASH_CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

BOOL duplicate_hash_impl(ALG_ID aiAlgid, const HASH_CONTEXT *pSrcHashContext,
                         HASH_CONTEXT *pDestHashContext) 
{
    *pDestHashContext = *pSrcHashContext;

    return TRUE;
}