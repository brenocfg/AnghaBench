#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ITERATIONS_SHORT ; 
 int /*<<< orphan*/  SONYPI_CAMERA_AGC ; 
 int /*<<< orphan*/  SONYPI_CAMERA_BRIGHTNESS ; 
 int /*<<< orphan*/  SONYPI_CAMERA_COLOR ; 
 int /*<<< orphan*/  SONYPI_CAMERA_CONTRAST ; 
 int /*<<< orphan*/  SONYPI_CAMERA_HUE ; 
 int /*<<< orphan*/  SONYPI_CAMERA_PICTURE ; 
 int /*<<< orphan*/  SONYPI_CAMERA_SHARPNESS ; 
#define  SONY_PIC_COMMAND_SETCAMERA 135 
#define  SONY_PIC_COMMAND_SETCAMERAAGC 134 
#define  SONY_PIC_COMMAND_SETCAMERABRIGHTNESS 133 
#define  SONY_PIC_COMMAND_SETCAMERACOLOR 132 
#define  SONY_PIC_COMMAND_SETCAMERACONTRAST 131 
#define  SONY_PIC_COMMAND_SETCAMERAHUE 130 
#define  SONY_PIC_COMMAND_SETCAMERAPICTURE 129 
#define  SONY_PIC_COMMAND_SETCAMERASHARPNESS 128 
 int /*<<< orphan*/  __sony_pic_camera_off () ; 
 int /*<<< orphan*/  __sony_pic_camera_on () ; 
 int /*<<< orphan*/  camera ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  sony_pic_call3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ spic_dev ; 
 int /*<<< orphan*/  wait_on_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sony_pic_camera_command(int command, u8 value)
{
	if (!camera)
		return -EIO;

	mutex_lock(&spic_dev.lock);

	switch (command) {
	case SONY_PIC_COMMAND_SETCAMERA:
		if (value)
			__sony_pic_camera_on();
		else
			__sony_pic_camera_off();
		break;
	case SONY_PIC_COMMAND_SETCAMERABRIGHTNESS:
		wait_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_BRIGHTNESS, value),
				ITERATIONS_SHORT);
		break;
	case SONY_PIC_COMMAND_SETCAMERACONTRAST:
		wait_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_CONTRAST, value),
				ITERATIONS_SHORT);
		break;
	case SONY_PIC_COMMAND_SETCAMERAHUE:
		wait_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_HUE, value),
				ITERATIONS_SHORT);
		break;
	case SONY_PIC_COMMAND_SETCAMERACOLOR:
		wait_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_COLOR, value),
				ITERATIONS_SHORT);
		break;
	case SONY_PIC_COMMAND_SETCAMERASHARPNESS:
		wait_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_SHARPNESS, value),
				ITERATIONS_SHORT);
		break;
	case SONY_PIC_COMMAND_SETCAMERAPICTURE:
		wait_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_PICTURE, value),
				ITERATIONS_SHORT);
		break;
	case SONY_PIC_COMMAND_SETCAMERAAGC:
		wait_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_AGC, value),
				ITERATIONS_SHORT);
		break;
	default:
		pr_err("sony_pic_camera_command invalid: %d\n", command);
		break;
	}
	mutex_unlock(&spic_dev.lock);
	return 0;
}