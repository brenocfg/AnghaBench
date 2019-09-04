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
struct smap_psock {int /*<<< orphan*/  bpf_verdict; int /*<<< orphan*/  bpf_parse; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 struct bpf_prog* xchg (int /*<<< orphan*/ *,struct bpf_prog*) ; 

__attribute__((used)) static void smap_init_progs(struct smap_psock *psock,
			    struct bpf_prog *verdict,
			    struct bpf_prog *parse)
{
	struct bpf_prog *orig_parse, *orig_verdict;

	orig_parse = xchg(&psock->bpf_parse, parse);
	orig_verdict = xchg(&psock->bpf_verdict, verdict);

	if (orig_verdict)
		bpf_prog_put(orig_verdict);
	if (orig_parse)
		bpf_prog_put(orig_parse);
}