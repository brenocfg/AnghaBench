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
struct nfs4_file {int /*<<< orphan*/  fi_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void get_nfs4_file(struct nfs4_file *fi)
{
	refcount_inc(&fi->fi_ref);
}