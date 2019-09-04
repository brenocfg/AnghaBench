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
struct cxgbi_sock {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (int,char*,char const*,struct cxgbi_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __cxgbi_sock_get(const char *fn, struct cxgbi_sock *csk)
{
	log_debug(1 << CXGBI_DBG_SOCK,
		"%s, get csk 0x%p, ref %u+1.\n",
		fn, csk, kref_read(&csk->refcnt));
	kref_get(&csk->refcnt);
}