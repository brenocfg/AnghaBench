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
struct nfs_write_verifier {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
nfs_write_verifier_cmp(const struct nfs_write_verifier *v1,
		const struct nfs_write_verifier *v2)
{
	return memcmp(v1->data, v2->data, sizeof(v1->data));
}