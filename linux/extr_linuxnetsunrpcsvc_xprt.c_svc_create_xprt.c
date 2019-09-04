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

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 int _svc_create_xprt (struct svc_serv*,char const*,struct net*,int const,unsigned short const,int) ; 
 int /*<<< orphan*/  dprintk (char*,char const*,unsigned short const) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 

int svc_create_xprt(struct svc_serv *serv, const char *xprt_name,
		    struct net *net, const int family,
		    const unsigned short port, int flags)
{
	int err;

	dprintk("svc: creating transport %s[%d]\n", xprt_name, port);
	err = _svc_create_xprt(serv, xprt_name, net, family, port, flags);
	if (err == -EPROTONOSUPPORT) {
		request_module("svc%s", xprt_name);
		err = _svc_create_xprt(serv, xprt_name, net, family, port, flags);
	}
	if (err)
		dprintk("svc: transport %s not found, err %d\n",
			xprt_name, err);
	return err;
}