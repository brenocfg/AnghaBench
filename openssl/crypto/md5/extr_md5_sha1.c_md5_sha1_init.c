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
struct TYPE_3__ {int /*<<< orphan*/  sha1; int /*<<< orphan*/  md5; } ;
typedef  TYPE_1__ MD5_SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int SHA1_Init (int /*<<< orphan*/ *) ; 

int md5_sha1_init(MD5_SHA1_CTX *mctx)
{
    if (!MD5_Init(&mctx->md5))
        return 0;
    return SHA1_Init(&mctx->sha1);
}