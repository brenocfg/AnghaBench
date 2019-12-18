#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_14__ {int C2_SAMPLE_TIME; double C2_BLANKING_TIME; double C2_IDISS_TIME; int /*<<< orphan*/  C2_BRAKE_STAB; int /*<<< orphan*/  C2_BIDIR_INPUT; } ;
struct TYPE_20__ {scalar_t__ Byte; TYPE_3__ Bits; } ;
struct TYPE_15__ {int /*<<< orphan*/  C3_NG_THRESH; int /*<<< orphan*/  C3_ERM_OPEN_LOOP; int /*<<< orphan*/  C3_SUPPLY_COMP_DIS; int /*<<< orphan*/  C3_DATA_FORMAT_RTO; int /*<<< orphan*/  C3_LRA_DRIVE_MODE; int /*<<< orphan*/  C3_N_PWM_ANALOG; int /*<<< orphan*/  C3_LRA_OPEN_LOOP; } ;
struct TYPE_19__ {scalar_t__ Byte; TYPE_4__ Bits; } ;
struct TYPE_16__ {int /*<<< orphan*/  C4_AUTO_CAL_TIME; int /*<<< orphan*/  C4_ZC_DET_TIME; } ;
struct TYPE_18__ {scalar_t__ Byte; TYPE_5__ Bits; } ;
struct TYPE_12__ {scalar_t__ BEMF_GAIN; int /*<<< orphan*/  LOOP_GAIN; int /*<<< orphan*/  BRAKE_FACTOR; int /*<<< orphan*/  ERM_LRA; } ;
struct TYPE_17__ {scalar_t__ Byte; TYPE_1__ Bits; } ;
struct TYPE_13__ {double C1_DRIVE_TIME; int /*<<< orphan*/  C1_STARTUP_BOOST; int /*<<< orphan*/  C1_AC_COUPLE; } ;
struct TYPE_11__ {scalar_t__ Byte; TYPE_2__ Bits; } ;
typedef  TYPE_6__ DRVREG_FBR ;
typedef  TYPE_7__ DRVREG_CTRL4 ;
typedef  TYPE_8__ DRVREG_CTRL3 ;
typedef  TYPE_9__ DRVREG_CTRL2 ;
typedef  TYPE_10__ DRVREG_CTRL1 ;

/* Variables and functions */
 int /*<<< orphan*/  AC_COUPLE ; 
 int /*<<< orphan*/  AUTO_CAL_TIME ; 
 int /*<<< orphan*/  BIDIR_INPUT ; 
 double BLANKING_TIME ; 
 int /*<<< orphan*/  BRAKE_STAB ; 
 int /*<<< orphan*/  DATA_FORMAT_RTO ; 
 double DRIVE_TIME ; 
 int /*<<< orphan*/  DRV_CTRL_1 ; 
 int /*<<< orphan*/  DRV_CTRL_2 ; 
 int /*<<< orphan*/  DRV_CTRL_3 ; 
 int /*<<< orphan*/  DRV_CTRL_4 ; 
 int /*<<< orphan*/  DRV_FEEDBACK_CTRL ; 
 int /*<<< orphan*/  DRV_GO ; 
 int DRV_GREETING ; 
 int /*<<< orphan*/  DRV_LIB_SELECTION ; 
 int /*<<< orphan*/  DRV_MODE ; 
 int /*<<< orphan*/  DRV_OVERDRIVE_CLAMP_VOLT ; 
 int /*<<< orphan*/  DRV_RATED_VOLT ; 
 int /*<<< orphan*/  DRV_WAVEFORM_SEQ_1 ; 
 int /*<<< orphan*/  DRV_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERM_OPEN_LOOP ; 
 int /*<<< orphan*/  FB_BRAKEFACTOR ; 
 int /*<<< orphan*/  FB_ERM_LRA ; 
 int /*<<< orphan*/  FB_LOOPGAIN ; 
 int F_LRA ; 
 double IDISS_TIME ; 
 int LIB_SELECTION ; 
 int /*<<< orphan*/  LRA_DRIVE_MODE ; 
 int /*<<< orphan*/  LRA_OPEN_LOOP ; 
 int /*<<< orphan*/  NG_THRESH ; 
 int /*<<< orphan*/  N_PWM_ANALOG ; 
 double RATED_VOLTAGE ; 
 int SAMPLE_TIME ; 
 int /*<<< orphan*/  STARTUP_BOOST ; 
 int /*<<< orphan*/  SUPPLY_COMP_DIS ; 
 double V_PEAK ; 
 double V_RMS ; 
 int /*<<< orphan*/  ZC_DET_TIME ; 
 int /*<<< orphan*/  i2c_init () ; 
 double sqrt (int) ; 

void DRV_init(void) {
    i2c_init();
    /* 0x07 sets DRV2605 into calibration mode */
    DRV_write(DRV_MODE, 0x07);

    //  DRV_write(DRV_FEEDBACK_CTRL,0xB6);

#if FB_ERM_LRA == 0
    /* ERM settings */
    DRV_write(DRV_RATED_VOLT, (RATED_VOLTAGE / 21.33) * 1000);
#    if ERM_OPEN_LOOP == 0
    DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, (((V_PEAK * (DRIVE_TIME + BLANKING_TIME + IDISS_TIME)) / 0.02133) / (DRIVE_TIME - 0.0003)));
#    elif ERM_OPEN_LOOP == 1
    DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, (V_PEAK / 0.02196));
#    endif
#elif FB_ERM_LRA == 1
    DRV_write(DRV_RATED_VOLT, ((V_RMS * sqrt(1 - ((4 * ((150 + (SAMPLE_TIME * 50)) * 0.000001)) + 0.0003) * F_LRA) / 0.02071)));
#    if LRA_OPEN_LOOP == 0
    DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, ((V_PEAK / sqrt(1 - (F_LRA * 0.0008)) / 0.02133)));
#    elif LRA_OPEN_LOOP == 1
    DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, (V_PEAK / 0.02196));
#    endif
#endif

    DRVREG_FBR FB_SET;
    FB_SET.Bits.ERM_LRA      = FB_ERM_LRA;
    FB_SET.Bits.BRAKE_FACTOR = FB_BRAKEFACTOR;
    FB_SET.Bits.LOOP_GAIN    = FB_LOOPGAIN;
    FB_SET.Bits.BEMF_GAIN    = 0; /* auto-calibration populates this field*/
    DRV_write(DRV_FEEDBACK_CTRL, (uint8_t)FB_SET.Byte);
    DRVREG_CTRL1 C1_SET;
    C1_SET.Bits.C1_DRIVE_TIME    = DRIVE_TIME;
    C1_SET.Bits.C1_AC_COUPLE     = AC_COUPLE;
    C1_SET.Bits.C1_STARTUP_BOOST = STARTUP_BOOST;
    DRV_write(DRV_CTRL_1, (uint8_t)C1_SET.Byte);
    DRVREG_CTRL2 C2_SET;
    C2_SET.Bits.C2_BIDIR_INPUT   = BIDIR_INPUT;
    C2_SET.Bits.C2_BRAKE_STAB    = BRAKE_STAB;
    C2_SET.Bits.C2_SAMPLE_TIME   = SAMPLE_TIME;
    C2_SET.Bits.C2_BLANKING_TIME = BLANKING_TIME;
    C2_SET.Bits.C2_IDISS_TIME    = IDISS_TIME;
    DRV_write(DRV_CTRL_2, (uint8_t)C2_SET.Byte);
    DRVREG_CTRL3 C3_SET;
    C3_SET.Bits.C3_LRA_OPEN_LOOP   = LRA_OPEN_LOOP;
    C3_SET.Bits.C3_N_PWM_ANALOG    = N_PWM_ANALOG;
    C3_SET.Bits.C3_LRA_DRIVE_MODE  = LRA_DRIVE_MODE;
    C3_SET.Bits.C3_DATA_FORMAT_RTO = DATA_FORMAT_RTO;
    C3_SET.Bits.C3_SUPPLY_COMP_DIS = SUPPLY_COMP_DIS;
    C3_SET.Bits.C3_ERM_OPEN_LOOP   = ERM_OPEN_LOOP;
    C3_SET.Bits.C3_NG_THRESH       = NG_THRESH;
    DRV_write(DRV_CTRL_3, (uint8_t)C3_SET.Byte);
    DRVREG_CTRL4 C4_SET;
    C4_SET.Bits.C4_ZC_DET_TIME   = ZC_DET_TIME;
    C4_SET.Bits.C4_AUTO_CAL_TIME = AUTO_CAL_TIME;
    DRV_write(DRV_CTRL_4, (uint8_t)C4_SET.Byte);
    DRV_write(DRV_LIB_SELECTION, LIB_SELECTION);

    DRV_write(DRV_GO, 0x01);

    /* 0x00 sets DRV2605 out of standby and to use internal trigger
     * 0x01 sets DRV2605 out of standby and to use external trigger */
    DRV_write(DRV_MODE, 0x00);

    // Play greeting sequence
    DRV_write(DRV_GO, 0x00);
    DRV_write(DRV_WAVEFORM_SEQ_1, DRV_GREETING);
    DRV_write(DRV_GO, 0x01);
}