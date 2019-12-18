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
struct sk_filter {int /*<<< orphan*/  prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bpf_prog_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sk_filter*) ; 

__attribute__((used)) static void __sk_filter_release(struct sk_filter *fp)
{
	__bpf_prog_release(fp->prog);
	kfree(fp);
}