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
struct TYPE_2__ {int /*<<< orphan*/  h4; int /*<<< orphan*/  h3; int /*<<< orphan*/  h2; int /*<<< orphan*/  h1; int /*<<< orphan*/  h0; } ;
typedef  TYPE_1__ SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  l2n (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static void tls1_sha1_final_raw(void *ctx, unsigned char *md_out)
{
    SHA_CTX *sha1 = ctx;
    l2n(sha1->h0, md_out);
    l2n(sha1->h1, md_out);
    l2n(sha1->h2, md_out);
    l2n(sha1->h3, md_out);
    l2n(sha1->h4, md_out);
}