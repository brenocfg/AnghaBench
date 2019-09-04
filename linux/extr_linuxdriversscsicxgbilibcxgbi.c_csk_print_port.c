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
struct TYPE_2__ {int /*<<< orphan*/  sin_port; } ;
struct cxgbi_sock {TYPE_1__ daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int csk_print_port(struct cxgbi_sock *csk, char *buf)
{
	int len;

	cxgbi_sock_get(csk);
	len = sprintf(buf, "%hu\n", ntohs(csk->daddr.sin_port));
	cxgbi_sock_put(csk);

	return len;
}