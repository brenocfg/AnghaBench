#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int mp_int_t ;
struct TYPE_7__ {TYPE_1__* Instance; } ;
struct TYPE_6__ {int CALR; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_RTCEx_DeactivateCalibrationOutPut (TYPE_2__*) ; 
 int /*<<< orphan*/  HAL_RTCEx_SetCalibrationOutPut (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_RTCEx_SetSmoothCalib (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__ RTCHandle ; 
 int /*<<< orphan*/  RTC_CALIBOUTPUT_512HZ ; 
 int /*<<< orphan*/  RTC_SMOOTHCALIB_PERIOD_32SEC ; 
 int RTC_SMOOTHCALIB_PLUSPULSES_RESET ; 
 int RTC_SMOOTHCALIB_PLUSPULSES_SET ; 
 int /*<<< orphan*/  mp_const_none ; 
 int mp_obj_get_int (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mp_obj_new_int (int) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  rtc_init_finalise () ; 

mp_obj_t pyb_rtc_calibration(size_t n_args, const mp_obj_t *args) {
    rtc_init_finalise();
    mp_int_t cal;
    if (n_args == 2) {
        cal = mp_obj_get_int(args[1]);
        mp_uint_t cal_p, cal_m;
        if (cal < -511 || cal > 512) {
#if defined(MICROPY_HW_RTC_USE_CALOUT) && MICROPY_HW_RTC_USE_CALOUT
            if ((cal & 0xfffe) == 0x0ffe) {
                // turn on/off X18 (PC13) 512Hz output
                // Note:
                //      Output will stay active even in VBAT mode (and inrease current)
                if (cal & 1) {
                    HAL_RTCEx_SetCalibrationOutPut(&RTCHandle, RTC_CALIBOUTPUT_512HZ);
                } else {
                    HAL_RTCEx_DeactivateCalibrationOutPut(&RTCHandle);
                }
                return mp_obj_new_int(cal & 1);
            } else {
                mp_raise_ValueError("calibration value out of range");
            }
#else
            mp_raise_ValueError("calibration value out of range");
#endif
        }
        if (cal > 0) {
            cal_p = RTC_SMOOTHCALIB_PLUSPULSES_SET;
            cal_m = 512 - cal;
        } else {
            cal_p = RTC_SMOOTHCALIB_PLUSPULSES_RESET;
            cal_m = -cal;
        }
        HAL_RTCEx_SetSmoothCalib(&RTCHandle, RTC_SMOOTHCALIB_PERIOD_32SEC, cal_p, cal_m);
        return mp_const_none;
    } else {
        // printf("CALR = 0x%x\n", (mp_uint_t) RTCHandle.Instance->CALR); // DEBUG
        // Test if CALP bit is set in CALR:
        if (RTCHandle.Instance->CALR & 0x8000) {
            cal = 512 - (RTCHandle.Instance->CALR & 0x1ff);
        } else {
            cal = -(RTCHandle.Instance->CALR & 0x1ff);
        }
        return mp_obj_new_int(cal);
    }
}