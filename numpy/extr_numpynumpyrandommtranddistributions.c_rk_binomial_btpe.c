#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int has_binomial; long nsave; double psave; double r; double q; double fm; long m; double p1; double xm; double xl; double xr; double c; double laml; double lamr; double p2; double p3; double p4; } ;
typedef  TYPE_1__ rk_state ;

/* Variables and functions */
 double fabs (long) ; 
 double floor (double) ; 
 long labs (long) ; 
 long log (double) ; 
 double min (double,double) ; 
 double rk_double (TYPE_1__*) ; 
 double sqrt (long) ; 

long rk_binomial_btpe(rk_state *state, long n, double p)
{
    double r,q,fm,p1,xm,xl,xr,c,laml,lamr,p2,p3,p4;
    double a,u,v,s,F,rho,t,A,nrq,x1,x2,f1,f2,z,z2,w,w2,x;
    long m,y,k,i;

    if (!(state->has_binomial) ||
         (state->nsave != n) ||
         (state->psave != p))
    {
        /* initialize */
        state->nsave = n;
        state->psave = p;
        state->has_binomial = 1;
        state->r = r = min(p, 1.0-p);
        state->q = q = 1.0 - r;
        state->fm = fm = n*r+r;
        state->m = m = (long)floor(state->fm);
        state->p1 = p1 = floor(2.195*sqrt(n*r*q)-4.6*q) + 0.5;
        state->xm = xm = m + 0.5;
        state->xl = xl = xm - p1;
        state->xr = xr = xm + p1;
        state->c = c = 0.134 + 20.5/(15.3 + m);
        a = (fm - xl)/(fm-xl*r);
        state->laml = laml = a*(1.0 + a/2.0);
        a = (xr - fm)/(xr*q);
        state->lamr = lamr = a*(1.0 + a/2.0);
        state->p2 = p2 = p1*(1.0 + 2.0*c);
        state->p3 = p3 = p2 + c/laml;
        state->p4 = p4 = p3 + c/lamr;
    }
    else
    {
        r = state->r;
        q = state->q;
        fm = state->fm;
        m = state->m;
        p1 = state->p1;
        xm = state->xm;
        xl = state->xl;
        xr = state->xr;
        c = state->c;
        laml = state->laml;
        lamr = state->lamr;
        p2 = state->p2;
        p3 = state->p3;
        p4 = state->p4;
    }

  /* sigh ... */
  Step10:
    nrq = n*r*q;
    u = rk_double(state)*p4;
    v = rk_double(state);
    if (u > p1) goto Step20;
    y = (long)floor(xm - p1*v + u);
    goto Step60;

  Step20:
    if (u > p2) goto Step30;
    x = xl + (u - p1)/c;
    v = v*c + 1.0 - fabs(m - x + 0.5)/p1;
    if (v > 1.0) goto Step10;
    y = (long)floor(x);
    goto Step50;

  Step30:
    if (u > p3) goto Step40;
    y = (long)floor(xl + log(v)/laml);
    if (y < 0) goto Step10;
    v = v*(u-p2)*laml;
    goto Step50;

  Step40:
    y = (long)floor(xr - log(v)/lamr);
    if (y > n) goto Step10;
    v = v*(u-p3)*lamr;

  Step50:
    k = labs(y - m);
    if ((k > 20) && (k < ((nrq)/2.0 - 1))) goto Step52;

    s = r/q;
    a = s*(n+1);
    F = 1.0;
    if (m < y)
    {
        for (i=m+1; i<=y; i++)
        {
            F *= (a/i - s);
        }
    }
    else if (m > y)
    {
        for (i=y+1; i<=m; i++)
        {
            F /= (a/i - s);
        }
    }
    if (v > F) goto Step10;
    goto Step60;

    Step52:
    rho = (k/(nrq))*((k*(k/3.0 + 0.625) + 0.16666666666666666)/nrq + 0.5);
    t = -k*k/(2*nrq);
    A = log(v);
    if (A < (t - rho)) goto Step60;
    if (A > (t + rho)) goto Step10;

    x1 = y+1;
    f1 = m+1;
    z = n+1-m;
    w = n-y+1;
    x2 = x1*x1;
    f2 = f1*f1;
    z2 = z*z;
    w2 = w*w;
    if (A > (xm*log(f1/x1)
           + (n-m+0.5)*log(z/w)
           + (y-m)*log(w*r/(x1*q))
           + (13680.-(462.-(132.-(99.-140./f2)/f2)/f2)/f2)/f1/166320.
           + (13680.-(462.-(132.-(99.-140./z2)/z2)/z2)/z2)/z/166320.
           + (13680.-(462.-(132.-(99.-140./x2)/x2)/x2)/x2)/x1/166320.
           + (13680.-(462.-(132.-(99.-140./w2)/w2)/w2)/w2)/w/166320.))
    {
        goto Step10;
    }

  Step60:
    if (p > 0.5)
    {
        y = n - y;
    }

    return y;
}