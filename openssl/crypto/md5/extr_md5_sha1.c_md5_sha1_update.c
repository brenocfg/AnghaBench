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
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int SHA1_Update (int /*<<< orphan*/ *,void const*,size_t) ; 

int md5_sha1_update(MD5_SHA1_CTX *mctx, const void *data, size_t count)
{
    if (!MD5_Update(&mctx->md5, data, count))
        return 0;
    return SHA1_Update(&mctx->sha1, data, count);
}