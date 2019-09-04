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
struct rpcent {int dummy; } ;
struct rpcdata {int /*<<< orphan*/  line; int /*<<< orphan*/ * rpcf; } ;

/* Variables and functions */
 scalar_t__ BUFSIZ ; 
 int /*<<< orphan*/  RPCDB ; 
 struct rpcdata* _rpcdata () ; 
 int /*<<< orphan*/ * fgets (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 struct rpcent* interpret (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

struct rpcent *
getrpcent()
{
	struct rpcdata *d = _rpcdata();
#ifdef	YP
	struct rpcent *hp;
	int reason;
	char *val = NULL;
	int vallen;
#endif

	if (d == 0)
		return(NULL);
#ifdef	YP
        if (!__yp_nomap && _yp_check(&d->domain)) {
                if (d->current == NULL && d->currentlen == 0) {
                        reason = yp_first(d->domain, "rpc.bynumber",
                                          &d->current, &d->currentlen,
                                          &val, &vallen);
                } else {
                        reason = yp_next(d->domain, "rpc.bynumber",
                                         d->current, d->currentlen,
                                         &d->current, &d->currentlen,
                                         &val, &vallen);
                }
                switch(reason) {
                case 0:
                        break;
                case YPERR_MAP:
                        __yp_nomap = 1;
                        goto no_yp;
                        break;
                default:
                        return(0);
                        break;
                }
                val[vallen] = '\0';
                hp = interpret(val, vallen);
                (void) free(val);
                return hp;
        }
no_yp:
#endif	/* YP */
	if (d->rpcf == NULL && (d->rpcf = fopen(RPCDB, "r")) == NULL)
		return (NULL);
	/* -1 so there is room to append a \n below */
        if (fgets(d->line, BUFSIZ - 1, d->rpcf) == NULL)
		return (NULL);
	return (interpret(d->line, strlen(d->line)));
}