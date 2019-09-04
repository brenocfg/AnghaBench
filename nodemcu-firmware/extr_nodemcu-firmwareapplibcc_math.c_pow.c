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

/* Variables and functions */
 double HUGE ; 
 int MAXEXP ; 
 int MINEXP ; 
 double NAN ; 
 double* a1 ; 
 double* a2 ; 
 double g ; 
 double k ; 
 double ldexp (double,int) ; 
 double p1 ; 
 double p2 ; 
 double p3 ; 
 double p4 ; 
 double q1 ; 
 double q2 ; 
 double q3 ; 
 double q4 ; 
 double q5 ; 
 double q6 ; 
 double q7 ; 
 double r ; 
 double u1 ; 
 double u2 ; 
 double v ; 
 double w ; 
 double w1 ; 
 double w2 ; 
 double y1 ; 
 double y2 ; 
 double z ; 

double pow(double x, double y)
{
    double frexp(), g, ldexp(), r, u1, u2, v, w, w1, w2, y1, y2, z;
    int iw1, m, p;
    bool flipsignal = false;

    if (y == 0.0)
        return (1.0);
    if (x <= 0.0)
    {
        if (x == 0.0)
        {
            if (y > 0.0)
                return 0.0;
            //cmemsg(FP_POWO, &y);
            //return(HUGE);
        }
        else
        {
            //cmemsg(FP_POWN, &x);
            x = -x;

            if (y != (int) y) { // if y is fractional, then this woud result in a complex number
                return NAN;
            }
            flipsignal = ((int) y) & 1;
        }
    }
    g = frexp(x, &m);
    p = 0;
    if (g <= a1[8])
        p = 8;
    if (g <= a1[p + 4])
        p += 4;
    if (g <= a1[p + 2])
        p += 2;
    p++;
    z = ((g - a1[p]) - a2[p / 2]) / (g + a1[p]);
    z += z;
    v = z * z;
    r = (((p4 * v + p3) * v + p2) * v + p1) * v * z;
    r += k * r;
    u2 = (r + z * k) + z;
    u1 = 0.0625 * (double)(16 * m - p);
    y1 = 0.0625 * (double)((int)(16.0 * y));
    y2 = y - y1;
    w = u2 * y + u1 * y2;
    w1 = 0.0625 * (double)((int)(16.0 * w));
    w2 = w - w1;
    w = w1 + u1 * y1;
    w1 = 0.0625 * (double)((int)(16.0 * w));
    w2 += (w - w1);
    w = 0.0625 * (double)((int)(16.0 * w2));
    iw1 = 16.0 * (w1 + w);
    w2 -= w;
    while (w2 > 0.0)
    {
        iw1++;
        w2 -= 0.0625;
    }
    if (iw1 > MAXEXP)
    {
        //cmemsg(FP_POWO, &y);
        return (HUGE);
    }
    if (iw1 < MINEXP)
    {
        //cmemsg(FP_POWU, &y);
        return (0.0);
    }
    m = iw1 / 16;
    if (iw1 >= 0)
        m++;
    p = 16 * m - iw1;
    z = ((((((q7 * w2 + q6) * w2 + q5) * w2 + q4) * w2 + q3) * w2 + q2) * w2 + q1) * w2;
    z = a1[p] + a1[p] * z;
    double res = ldexp(z, m);
    return flipsignal ? -res : res;
}