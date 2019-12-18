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
typedef  int HPDF_REAL ;

/* Variables and functions */
 char* HPDF_FToA (char*,int,char*) ; 
 scalar_t__ HPDF_StrCpy (char*,char*,char*) ; 
 int KAPPA ; 

__attribute__((used)) static char*
QuarterCircleC  (char   *pbuf,
                 char   *eptr,
                 HPDF_REAL    x,
                 HPDF_REAL    y,
                 HPDF_REAL    ray)
{
    pbuf = HPDF_FToA (pbuf, x + ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - ray, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, y - ray, eptr);
    return (char *)HPDF_StrCpy (pbuf, " c\012", eptr);
}