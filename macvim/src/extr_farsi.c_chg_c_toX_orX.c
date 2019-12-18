#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  col; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_CURSOR ; 
 int AYN ; 
 int AYN_ ; 
 int BE ; 
 int CHE ; 
 int FE ; 
 int F_HE ; 
 int /*<<< orphan*/  F_is_TyB_TyC_TyD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GAF ; 
 int GHAF ; 
 int GHAYN ; 
 int GHAYN_ ; 
 int HE_J ; 
 int IE ; 
 int IE_ ; 
 int JIM ; 
 int KAF ; 
 int LAM ; 
 int MIM ; 
 int NOON ; 
 int PE ; 
 int SAD ; 
 int SE ; 
 int SHIN ; 
 int SIN ; 
 int /*<<< orphan*/  SRC_EDT ; 
 int TE ; 
 int XE ; 
 int YE ; 
 int YEE ; 
 int YEE_ ; 
 int YE_ ; 
 int ZAD ; 
#define  _AYN 156 
#define  _AYN_ 155 
#define  _BE 154 
#define  _CHE 153 
#define  _FE 152 
#define  _GAF 151 
#define  _GHAF 150 
#define  _GHAYN 149 
#define  _GHAYN_ 148 
#define  _HE 147 
#define  _HE_ 146 
#define  _HE_J 145 
#define  _IE 144 
#define  _JIM 143 
#define  _KAF 142 
#define  _KAF_H 141 
#define  _LAM 140 
#define  _MIM 139 
#define  _NOON 138 
#define  _PE 137 
#define  _SAD 136 
#define  _SE 135 
#define  _SHIN 134 
#define  _SIN 133 
#define  _TE 132 
#define  _XE 131 
#define  _YE 130 
#define  _YEE 129 
#define  _ZAD 128 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  dec_cursor () ; 
 int gchar_cursor () ; 
 int /*<<< orphan*/  inc_cursor () ; 
 int /*<<< orphan*/  p_ri ; 
 int /*<<< orphan*/  put_and_redo (int) ; 

__attribute__((used)) static void
chg_c_toX_orX()
{
    int	tempc, curc;

    switch ((curc = gchar_cursor()))
    {
	case _BE:
		tempc = BE;
		break;
	case _PE:
		tempc = PE;
		break;
	case _TE:
		tempc = TE;
		break;
	case _SE:
		tempc = SE;
		break;
	case _JIM:
		tempc = JIM;
		break;
	case _CHE:
		tempc = CHE;
		break;
	case _HE_J:
		tempc = HE_J;
		break;
	case _XE:
		tempc = XE;
		break;
	case _SIN:
		tempc = SIN;
		break;
	case _SHIN:
		tempc = SHIN;
		break;
	case _SAD:
		tempc = SAD;
		break;
	case _ZAD:
		tempc = ZAD;
		break;
	case _FE:
		tempc = FE;
		break;
	case _GHAF:
		tempc = GHAF;
		break;
	case _KAF_H:
	case _KAF:
		tempc = KAF;
		break;
	case _GAF:
		tempc = GAF;
		break;
	case _AYN:
		tempc = AYN;
		break;
	case _AYN_:
		tempc = AYN_;
		break;
	case _GHAYN:
		tempc = GHAYN;
		break;
	case _GHAYN_:
		tempc = GHAYN_;
		break;
	case _LAM:
		tempc = LAM;
		break;
	case _MIM:
		tempc = MIM;
		break;
	case _NOON:
		tempc = NOON;
		break;
	case _HE:
	case _HE_:
		tempc = F_HE;
		break;
	case _YE:
	case _IE:
	case _YEE:
		if (p_ri)
		{
		    inc_cursor();
		    if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR))
			    tempc = (curc == _YE ? YE_ :
			    (curc == _IE ? IE_ : YEE_));
		    else
			    tempc = (curc == _YE ? YE :
			    (curc == _IE ? IE : YEE));
		    dec_cursor();
		}
		else
		{
		    if (curwin->w_cursor.col)
		    {
			dec_cursor();
			if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR))
				tempc = (curc == _YE ? YE_ :
				(curc == _IE ? IE_ : YEE_));
			else
				tempc = (curc == _YE ? YE :
				(curc == _IE ? IE : YEE));
			inc_cursor();
		    }
		    else
			    tempc = (curc == _YE ? YE :
			    (curc == _IE ? IE : YEE));
		}
		break;
	default:
		tempc = 0;
    }

    if (tempc)
	put_and_redo(tempc);
}