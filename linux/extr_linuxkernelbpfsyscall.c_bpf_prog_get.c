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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 struct bpf_prog* __bpf_prog_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

struct bpf_prog *bpf_prog_get(u32 ufd)
{
	return __bpf_prog_get(ufd, NULL, false);
}