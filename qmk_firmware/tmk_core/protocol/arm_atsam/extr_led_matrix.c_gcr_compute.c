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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ ACT_GCR_DEC ; 
 scalar_t__ ACT_GCR_INC ; 
 scalar_t__ ACT_GCR_NONE ; 
 int /*<<< orphan*/  CDC_print (char*) ; 
 int /*<<< orphan*/  I2C3733_Control_Set (int) ; 
 scalar_t__ LED_GCR_MAX ; 
 scalar_t__ LED_GCR_STEP_AUTO ; 
 scalar_t__ USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG ; 
 scalar_t__ USB_EXTRA_STATE_ENABLED ; 
 int /*<<< orphan*/  USB_ExtraSetState (scalar_t__) ; 
 scalar_t__ V5_CAT ; 
 scalar_t__ V5_HIGH ; 
 scalar_t__ V5_LOW ; 
 scalar_t__ gcr_actual ; 
 scalar_t__ gcr_breathe ; 
 scalar_t__ gcr_desired ; 
 int gcr_min_counter ; 
 int led_animation_breathing ; 
 scalar_t__ usb_extra_manual ; 
 scalar_t__ usb_extra_state ; 
 int usb_gcr_auto ; 
 scalar_t__ v_5v ; 
 scalar_t__ v_5v_avg ; 
 int v_5v_cat_hit ; 

void gcr_compute(void) {
    uint8_t action  = ACT_GCR_NONE;
    uint8_t gcr_use = gcr_desired;

#ifdef USE_MASSDROP_CONFIGURATOR
    if (led_animation_breathing) {
        gcr_use = gcr_breathe;
    }
#endif

    // If the 5v takes a catastrophic hit, disable the LED drivers briefly, assert auto gcr mode, min gcr and let the auto take over
    if (v_5v < V5_CAT) {
        I2C3733_Control_Set(0);
        // CDC_print("USB: WARNING: 5V catastrophic level reached! Disabling LED drivers!\r\n"); //Blocking print is bad here!
        v_5v_cat_hit = 20;  //~100ms recover
        gcr_actual   = 0;   // Minimize GCR
        usb_gcr_auto = 1;   // Force auto mode enabled
        return;
    } else if (v_5v_cat_hit > 1) {
        v_5v_cat_hit--;
        return;
    } else if (v_5v_cat_hit == 1) {
        I2C3733_Control_Set(1);
        CDC_print("USB: WARNING: Re-enabling LED drivers\r\n");
        v_5v_cat_hit = 0;
        return;
    }

    if (usb_gcr_auto) {
        if (v_5v_avg < V5_LOW)
            action = ACT_GCR_DEC;
        else if (v_5v_avg > V5_HIGH && gcr_actual < gcr_use)
            action = ACT_GCR_INC;
        else if (gcr_actual > gcr_use)
            action = ACT_GCR_DEC;
    } else {
        if (gcr_actual < gcr_use)
            action = ACT_GCR_INC;
        else if (gcr_actual > gcr_use)
            action = ACT_GCR_DEC;
    }

    if (action == ACT_GCR_NONE) {
        gcr_min_counter = 0;
    } else if (action == ACT_GCR_INC) {
        if (LED_GCR_STEP_AUTO > LED_GCR_MAX - gcr_actual)
            gcr_actual = LED_GCR_MAX;  // Obey max and prevent wrapping
        else
            gcr_actual += LED_GCR_STEP_AUTO;
        gcr_min_counter = 0;
    } else if (action == ACT_GCR_DEC) {
        if (LED_GCR_STEP_AUTO > gcr_actual)  // Prevent wrapping
        {
            gcr_actual = 0;
            // At this point, power can no longer be cut from the LED drivers, so focus on cutting out extra port if active
            if (usb_extra_state != USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG)  // If not in a wait for replug state
            {
                if (usb_extra_state == USB_EXTRA_STATE_ENABLED)  // If extra usb is enabled
                {
                    gcr_min_counter++;
                    if (gcr_min_counter > 200)  // 5ms per check = 1s delay
                    {
                        USB_ExtraSetState(USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG);
                        usb_extra_manual = 0;  // Force disable manual mode of extra port
                        if (usb_extra_manual)
                            CDC_print("USB: Disabling extra port until replug and manual mode toggle!\r\n");
                        else
                            CDC_print("USB: Disabling extra port until replug!\r\n");
                    }
                }
            }
        } else {
            // Power successfully cut back from LED drivers
            gcr_actual -= LED_GCR_STEP_AUTO;
            gcr_min_counter = 0;

#ifdef USE_MASSDROP_CONFIGURATOR
            // If breathe mode is active, the top end can fluctuate if the host can not supply enough current
            // So set the breathe GCR to where it becomes stable
            if (led_animation_breathing == 1) {
                gcr_breathe = gcr_actual;
                // PS: At this point, setting breathing to exhale makes a noticebly shorter cycle
                //    and the same would happen maybe one or two more times. Therefore I'm favoring
                //    powering through one full breathe and letting gcr settle completely
            }
#endif
        }
    }
}