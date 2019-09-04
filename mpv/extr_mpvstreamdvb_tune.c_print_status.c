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
typedef  int fe_status_t ;
typedef  int /*<<< orphan*/  dvb_priv_t ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int FE_TIMEDOUT ; 
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void print_status(dvb_priv_t *priv, fe_status_t festatus)
{
    MP_VERBOSE(priv, "FE_STATUS:");
    if (festatus & FE_HAS_SIGNAL)
        MP_VERBOSE(priv, " FE_HAS_SIGNAL");
    if (festatus & FE_TIMEDOUT)
        MP_VERBOSE(priv, " FE_TIMEDOUT");
    if (festatus & FE_HAS_LOCK)
        MP_VERBOSE(priv, " FE_HAS_LOCK");
    if (festatus & FE_HAS_CARRIER)
        MP_VERBOSE(priv, " FE_HAS_CARRIER");
    if (festatus & FE_HAS_VITERBI)
        MP_VERBOSE(priv, " FE_HAS_VITERBI");
    if (festatus & FE_HAS_SYNC)
        MP_VERBOSE(priv, " FE_HAS_SYNC");
    MP_VERBOSE(priv, "\n");
}