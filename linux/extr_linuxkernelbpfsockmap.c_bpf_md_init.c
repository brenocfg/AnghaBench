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
struct smap_psock {int /*<<< orphan*/ * sk_redir; int /*<<< orphan*/  eval; int /*<<< orphan*/  apply_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  __SK_NONE ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void bpf_md_init(struct smap_psock *psock)
{
	if (!psock->apply_bytes) {
		psock->eval =  __SK_NONE;
		if (psock->sk_redir) {
			sock_put(psock->sk_redir);
			psock->sk_redir = NULL;
		}
	}
}