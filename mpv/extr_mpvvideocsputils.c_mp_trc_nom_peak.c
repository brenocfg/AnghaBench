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
typedef  enum mp_csp_trc { ____Placeholder_mp_csp_trc } mp_csp_trc ;

/* Variables and functions */
#define  MP_CSP_TRC_HLG 132 
#define  MP_CSP_TRC_PQ 131 
#define  MP_CSP_TRC_S_LOG1 130 
#define  MP_CSP_TRC_S_LOG2 129 
#define  MP_CSP_TRC_V_LOG 128 
 double MP_REF_WHITE ; 

float mp_trc_nom_peak(enum mp_csp_trc trc)
{
    switch (trc) {
    case MP_CSP_TRC_PQ:           return 10000.0 / MP_REF_WHITE;
    case MP_CSP_TRC_HLG:          return 12.0;
    case MP_CSP_TRC_V_LOG:        return 46.0855;
    case MP_CSP_TRC_S_LOG1:       return 6.52;
    case MP_CSP_TRC_S_LOG2:       return 9.212;
    }

    return 1.0;
}