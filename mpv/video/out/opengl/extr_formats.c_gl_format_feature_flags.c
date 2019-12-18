#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int version; int es; int mpgl_caps; } ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int F_APPL ; 
 int F_ES2 ; 
 int F_ES3 ; 
 int F_ES32 ; 
 int F_EXT16 ; 
 int F_EXTF16 ; 
 int F_GL2 ; 
 int F_GL2F ; 
 int F_GL3 ; 
 int MPGL_CAP_APPLE_RGB_422 ; 
 int MPGL_CAP_ARB_FLOAT ; 
 int MPGL_CAP_EXT16 ; 
 int MPGL_CAP_EXT_CR_HFLOAT ; 
 int MPGL_CAP_FB ; 
 int MPGL_CAP_TEX_RG ; 

int gl_format_feature_flags(GL *gl)
{
    return (gl->version == 210 ? F_GL2 : 0)
         | (gl->version >= 300 ? F_GL3 : 0)
         | (gl->es == 200 ? F_ES2 : 0)
         | (gl->es >= 300 ? F_ES3 : 0)
         | (gl->es >= 320 ? F_ES32 : 0)
         | (gl->mpgl_caps & MPGL_CAP_EXT16 ? F_EXT16 : 0)
         | ((gl->es >= 300 &&
            (gl->mpgl_caps & MPGL_CAP_EXT_CR_HFLOAT)) ? F_EXTF16 : 0)
         | ((gl->version == 210 &&
            (gl->mpgl_caps & MPGL_CAP_ARB_FLOAT) &&
            (gl->mpgl_caps & MPGL_CAP_TEX_RG) &&
            (gl->mpgl_caps & MPGL_CAP_FB)) ? F_GL2F : 0)
         | (gl->mpgl_caps & MPGL_CAP_APPLE_RGB_422 ? F_APPL : 0);
}