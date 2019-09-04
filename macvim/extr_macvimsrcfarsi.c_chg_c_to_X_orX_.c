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
#define  ALEF 138 
 int ALEF_ ; 
#define  ALEF_U_H 137 
 int ALEF_U_H_ ; 
#define  AYN 136 
 int AYN_ ; 
#define  GHAYN 135 
 int GHAYN_ ; 
#define  IE 134 
 int IE_ ; 
#define  TEE 133 
 int TEE_ ; 
#define  YE 132 
#define  YEE 131 
 int YEE_ ; 
 int YE_ ; 
#define  _AYN 130 
 int _AYN_ ; 
#define  _GHAYN 129 
 int _GHAYN_ ; 
#define  _HE 128 
 int _HE_ ; 
 int gchar_cursor () ; 
 int /*<<< orphan*/  put_and_redo (int) ; 

__attribute__((used)) static void
chg_c_to_X_orX_()
{
    int	tempc;

    switch (gchar_cursor())
    {
	case ALEF:
		tempc = ALEF_;
		break;
	case ALEF_U_H:
		tempc = ALEF_U_H_;
		break;
	case _AYN:
		tempc = _AYN_;
		break;
	case AYN:
		tempc = AYN_;
		break;
	case _GHAYN:
		tempc = _GHAYN_;
		break;
	case GHAYN:
		tempc = GHAYN_;
		break;
	case _HE:
		tempc = _HE_;
		break;
	case YE:
		tempc = YE_;
		break;
	case IE:
		tempc = IE_;
		break;
	case TEE:
		tempc = TEE_;
		break;
	case YEE:
		tempc = YEE_;
		break;
	default:
		tempc = 0;
    }

    if (tempc)
	put_and_redo(tempc);
}