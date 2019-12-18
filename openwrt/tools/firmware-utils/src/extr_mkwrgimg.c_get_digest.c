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
struct wrg_header {int /*<<< orphan*/  digest; int /*<<< orphan*/  devname; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void get_digest(struct wrg_header *header, char *data, int size)
{
	MD5_CTX ctx;

	MD5_Init(&ctx);

	MD5_Update(&ctx, (char *)&header->offset, sizeof(header->offset));
	MD5_Update(&ctx, (char *)&header->devname, sizeof(header->devname));
	MD5_Update(&ctx, data, size);

	MD5_Final(header->digest, &ctx);
}