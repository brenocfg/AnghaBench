#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  v; int /*<<< orphan*/  s; int /*<<< orphan*/  h; } ;
struct TYPE_10__ {TYPE_1__ hsv; scalar_t__ enable; } ;
struct TYPE_9__ {int s; int v; int /*<<< orphan*/  h; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int r; int g; int b; } ;
typedef  TYPE_2__ RGB ;
typedef  TYPE_3__ HSV ;

/* Variables and functions */
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
#define  _FNC 130 
#define  _NAV 129 
#define  _RGB 128 
 int /*<<< orphan*/  autoshift_enabled ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_suspend_state ; 
 int host_keyboard_leds () ; 
 TYPE_2__ hsv_to_rgb (TYPE_3__) ; 
 int /*<<< orphan*/  layer_state ; 
 TYPE_4__ rgb_matrix_config ; 
 int /*<<< orphan*/  rgb_matrix_set_color (int,int,int,int) ; 

void rgb_matrix_indicators_user(void)
{
	uint8_t this_led = host_keyboard_leds();

	if (!g_suspend_state && rgb_matrix_config.enable) {
		switch (biton32(layer_state)) {
		case _NAV:
			if (this_led & (1 << USB_LED_NUM_LOCK)) {
				rgb_matrix_set_color(13, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(19, 0xFF, 0xFF, 0x00);
			} else {
				rgb_matrix_set_color(13, 0x00, 0x00, 0x00);
				rgb_matrix_set_color(19, 0xFF, 0x00, 0x00);
			}

			rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF); // layer indicator
			// ESDF
			rgb_matrix_set_color(24, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(38, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(37, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(36, 0xFF, 0x00, 0x00);
			// home/end
			rgb_matrix_set_color(25, 0x00, 0xFF, 0x00);
			rgb_matrix_set_color(23, 0x00, 0xFF, 0x00);
			// pgup/dn
			rgb_matrix_set_color(26, 0x00, 0x00, 0xFF);
			rgb_matrix_set_color(39, 0x00, 0x00, 0xFF);
			// numpad
			rgb_matrix_set_color(6,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(5,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(4,  0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(20, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(18, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(33, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(32, 0xFF, 0xFF, 0x00);
			rgb_matrix_set_color(31, 0xFF, 0xFF, 0x00);
			// zero
			rgb_matrix_set_color(47, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(46, 0xFF, 0x00, 0x00);
			rgb_matrix_set_color(45, 0xFF, 0x00, 0x00);
			// dot
			rgb_matrix_set_color(44, 0x00, 0x00, 0xFF);
			// math shit
			rgb_matrix_set_color(3,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(2,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(1,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(0,  0x00, 0x00, 0xFF);
			rgb_matrix_set_color(17, 0x00, 0x00, 0xFF);
			// other
			rgb_matrix_set_color(16, 0xFF, 0xFF, 0xFF);
			rgb_matrix_set_color(15, 0xFF, 0xFF, 0xFF);
			rgb_matrix_set_color(14, 0xFF, 0xFF, 0xFF);
			break;

		case _RGB: {
			HSV hsv = { rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
			HSV hui = hsv;
			HSV hud = hsv;
			HSV sai = hsv;
			HSV sad = hsv;
			HSV vai = hsv;
			HSV vad = hsv;
			hui.h = hsv.h + 8;
			hud.h = hsv.h - 8;
			sai.s = hsv.s + 16 > 255 ? 255 : hsv.s + 16;
			sad.s = hsv.s - 16 < 0   ?   0 : hsv.s - 16;
			vai.v = hsv.v + 16 > 255 ? 255 : hsv.v + 16;
			vad.v = hsv.v - 16 < 0   ?   0 : hsv.v - 16;
			RGB rgb = hsv_to_rgb(hsv);
			RGB rgbHUI = hsv_to_rgb(hui);
			RGB rgbHUD = hsv_to_rgb(hud);
			RGB rgbSAI = hsv_to_rgb(sai);
			RGB rgbSAD = hsv_to_rgb(sad);
			RGB rgbVAI = hsv_to_rgb(vai);
			RGB rgbVAD = hsv_to_rgb(vad);
			rgb_matrix_set_color(41, 0xFF, 0xFF, 0xFF); // layer indicator
			rgb_matrix_set_color(59, rgb.r, rgb.g, rgb.b); // color indicator
			rgb_matrix_set_color(26, 0xFF, 0x80, 0x00); //MOD
			rgb_matrix_set_color(39, 0xFF, 0x80, 0x00); //MOD
			rgb_matrix_set_color(16, 0xFF, 0x80, 0x00); //RGB_RMOD
			rgb_matrix_set_color(15, 0xFF, 0x80, 0x00); //MOD
			rgb_matrix_set_color(52, 0xFF, 0x40, 0x00); //TOG
			rgb_matrix_set_color(25, 0x80, 0x80, 0x80); //SPI
			rgb_matrix_set_color(38, 0x80, 0x80, 0x80); //SPD
			rgb_matrix_set_color(24, rgbHUI.r, rgbHUI.g, rgbHUI.b); //HUI
			rgb_matrix_set_color(37, rgbHUD.r, rgbHUD.g, rgbHUD.b); //HUD
			rgb_matrix_set_color(23, rgbSAI.r, rgbSAI.g, rgbSAI.b); //SAI
			rgb_matrix_set_color(36, rgbSAD.r, rgbSAD.g, rgbSAD.b); //SAD
			rgb_matrix_set_color(22, rgbVAI.r, rgbVAI.g, rgbVAI.b); //VAI
			rgb_matrix_set_color(35, rgbVAD.r, rgbVAD.g, rgbVAD.b); //VAD
			rgb_matrix_set_color(19, 0xF0, 0x00, 0xFF); //MAS_MGT
			rgb_matrix_set_color(18, 0x00, 0x02, 0xFF); //MAS_BLU
			rgb_matrix_set_color(33, 0xFF, 0x00, 0x00); //MAS_RED
			rgb_matrix_set_color(32, 0x00, 0x00, 0x00); //MAS_KEY
			rgb_matrix_set_color(31, 0x00, 0xFF, 0xF7); //MAS_CYN
			rgb_matrix_set_color(46, 0xFF, 0xDA, 0x00); //MAS_YEL
			rgb_matrix_set_color(45, 0x00, 0xFF, 0x01); //MAS_GRN
			rgb_matrix_set_color(44, 0xFF, 0xA5, 0x18); //MAS_CRM
			rgb_matrix_set_color(30, 0x81, 0x3C, 0xFF); //MAS_PRP
			rgb_matrix_set_color(17, 0xFF, 0xFF, 0xFF); //MAS_WHT
		}
		break;

		case _FNC:
			rgb_matrix_set_color(57, 0xFF, 0xFF, 0xFF); // layer indicator
			rgb_matrix_set_color(48, 0xFF, 0x00, 0x00); // bootloader
			rgb_matrix_set_color(42, 0x00, 0x80, 0xFF); // vol
			rgb_matrix_set_color(55, 0x00, 0x80, 0xFF);
			rgb_matrix_set_color(58, 0xFF, 0x00, 0x00); // mute
			rgb_matrix_set_color(56, 0xFF, 0x80, 0x00); // ctrl+left/right
			rgb_matrix_set_color(54, 0xFF, 0x80, 0x00);
			rgb_matrix_set_color(41, 0xFF, 0x00, 0x40); // ctrl+delete
			rgb_matrix_set_color(43, 0xFF, 0x00, 0x40); // ctrl+slash

			if (this_led & (1 << !autoshift_enabled)) {
				rgb_matrix_set_color(0, 0xFF, 0x00, 0x00); // KC_ASTG
			} else {
				rgb_matrix_set_color(0, 0xFF, 0xFF, 0x00);
			}

			break;
		}
	}

	if (this_led & (1 << USB_LED_CAPS_LOCK)) {
		rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	}
}