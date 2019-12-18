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
struct svc_serv {int dummy; } ;
struct net {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int create_lockd_listener (struct svc_serv*,char*,struct net*,int const,int /*<<< orphan*/ ,struct cred const*) ; 
 int /*<<< orphan*/  nlm_tcpport ; 
 int /*<<< orphan*/  nlm_udpport ; 

__attribute__((used)) static int create_lockd_family(struct svc_serv *serv, struct net *net,
			       const int family, const struct cred *cred)
{
	int err;

	err = create_lockd_listener(serv, "udp", net, family, nlm_udpport,
			cred);
	if (err < 0)
		return err;

	return create_lockd_listener(serv, "tcp", net, family, nlm_tcpport,
			cred);
}