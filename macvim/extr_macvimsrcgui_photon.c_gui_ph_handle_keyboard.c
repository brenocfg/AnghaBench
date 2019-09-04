#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ key_sym; int vim_code1; int vim_code0; } ;
struct TYPE_8__ {int key_flags; scalar_t__ key_cap; int key_mods; } ;
struct TYPE_7__ {int /*<<< orphan*/  event; } ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  TYPE_1__ PtCallbackInfo_t ;
typedef  TYPE_2__ PhKeyEvent_t ;

/* Variables and functions */
 unsigned char CSI ; 
 int Ctrl_C ; 
 int Ctrl_chr (int) ; 
 scalar_t__ IS_SPECIAL (int) ; 
 unsigned char KE_CSI ; 
 unsigned char KS_EXTRA ; 
 unsigned char KS_MODIFIER ; 
 unsigned char K_SECOND (int) ; 
 unsigned char K_THIRD (int) ; 
 int MOD_MASK_ALT ; 
 int MOD_MASK_CTRL ; 
 int MOD_MASK_SHIFT ; 
 int /*<<< orphan*/  MOUSE_HIDE ; 
 int Meta (int) ; 
 int NUL ; 
 TYPE_2__* PhGetData (int /*<<< orphan*/ ) ; 
 int PhTo8859_1 (TYPE_2__*) ; 
 scalar_t__ PkIsKeyDown (int) ; 
 int Pk_KF_Cap_Valid ; 
 int Pk_KF_Compose ; 
 int Pk_KM_Alt ; 
 int Pk_KM_Ctrl ; 
 int Pk_KM_Num_Lock ; 
 int Pk_KM_Shift ; 
 scalar_t__ Pk_KP_9 ; 
 scalar_t__ Pk_KP_Enter ; 
 int Pt_CONSUME ; 
 int Pt_CONTINUE ; 
 int TO_SPECIAL (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_to_input_buf (unsigned char*,int) ; 
 scalar_t__ ctrl_c_interrupts ; 
 int /*<<< orphan*/  got_int ; 
 int /*<<< orphan*/  gui_mch_mousehide (int /*<<< orphan*/ ) ; 
 int intr_char ; 
 scalar_t__ p_mh ; 
 int simplify_key (int,int*) ; 
 TYPE_3__* special_keys ; 
 int /*<<< orphan*/  trash_input_buf () ; 

__attribute__((used)) static int
gui_ph_handle_keyboard(PtWidget_t *widget, void *data, PtCallbackInfo_t *info)
{
    PhKeyEvent_t    *key;
    unsigned char   string[6];
    int		    len, i;
    int		    ch, modifiers;

    key = PhGetData(info->event);

    ch = modifiers = len = 0;

    if (p_mh)
	gui_mch_mousehide(MOUSE_HIDE);

    /* We're a good lil photon program, aren't we? yes we are, yeess wee arrr */
    if (key->key_flags & Pk_KF_Compose)
    {
	return Pt_CONTINUE;
    }

    if ((key->key_flags & Pk_KF_Cap_Valid) &&
	    PkIsKeyDown(key->key_flags))
    {
#ifdef FEAT_MENU
	/*
	 * Only show the menu if the Alt key is down, and the Shift & Ctrl
	 * keys aren't down, as well as the other conditions
	 */
	if (((key->key_mods & Pk_KM_Alt) &&
		    !(key->key_mods & Pk_KM_Shift) &&
		    !(key->key_mods & Pk_KM_Ctrl)) &&
	    gui.menu_is_active &&
	    (*p_wak == 'y' ||
	      (*p_wak == 'm' &&
		gui_is_menu_shortcut(key->key_cap))))
	{
	    /* Fallthrough and let photon look for the hotkey */
	    return Pt_CONTINUE;
	}
#endif

	for (i = 0; special_keys[i].key_sym != 0; i++)
	{
	    if (special_keys[i].key_sym == key->key_cap)
	    {
		len = 0;
		if (special_keys[i].vim_code1 == NUL)
		    ch = special_keys[i].vim_code0;
		else
		{
		    /* Detect if a keypad number key has been pressed
		     * and change the key if Num Lock is on */
		    if (key->key_cap >= Pk_KP_Enter && key->key_cap <= Pk_KP_9
			    && (key->key_mods & Pk_KM_Num_Lock))
		    {
			/* FIXME: For now, just map the key to a ascii value
			 * (see <photon/PkKeyDef.h>) */
			ch = key->key_cap - 0xf080;
		    }
		    else
			ch = TO_SPECIAL(special_keys[i].vim_code0,
				special_keys[i].vim_code1);
		}
		break;
	    }
	}

	if (key->key_mods & Pk_KM_Ctrl)
	    modifiers |= MOD_MASK_CTRL;
	if (key->key_mods & Pk_KM_Alt)
	    modifiers |= MOD_MASK_ALT;
	if (key->key_mods & Pk_KM_Shift)
	    modifiers |= MOD_MASK_SHIFT;

	/* Is this not a special key? */
	if (special_keys[i].key_sym == 0)
	{
	    ch = PhTo8859_1(key);
	    if (ch == -1
#ifdef FEAT_MBYTE
		|| (enc_utf8 && ch > 127)
#endif
		)
	    {
#ifdef FEAT_MBYTE
		len = PhKeyToMb(string, key);
		if (len > 0)
		{
		    static char buf[6];
		    int src_taken, dst_made;
		    if (enc_utf8 != TRUE)
		    {
			PxTranslateFromUTF(
				charset_translate,
				string,
				len,
				&src_taken,
				buf,
				6,
				&dst_made);

			add_to_input_buf(buf, dst_made);
		    }
		    else
		    {
			add_to_input_buf(string, len);
		    }

		    return Pt_CONSUME;
		}
		len = 0;
#endif
		ch = key->key_cap;
		if (ch < 0xff)
		{
		    /* FIXME: is this the right thing to do? */
		    if (modifiers & MOD_MASK_CTRL)
		    {
			modifiers &= ~MOD_MASK_CTRL;

			if ((ch >= 'a' && ch <= 'z') ||
				ch == '[' ||
				ch == ']' ||
				ch == '\\')
			    ch = Ctrl_chr(ch);
			else if (ch == '2')
			    ch = NUL;
			else if (ch == '6')
			    ch = 0x1e;
			else if (ch == '-')
			    ch = 0x1f;
			else
			    modifiers |= MOD_MASK_CTRL;
		    }

		    if (modifiers & MOD_MASK_ALT)
		    {
			ch = Meta(ch);
			modifiers &= ~MOD_MASK_ALT;
		    }
		}
		else
		{
		    return Pt_CONTINUE;
		}
	    }
	    else
		modifiers &= ~MOD_MASK_SHIFT;
	}

	ch = simplify_key(ch, &modifiers);
	if (modifiers)
	{
	    string[ len++ ] = CSI;
	    string[ len++ ] = KS_MODIFIER;
	    string[ len++ ] = modifiers;
	}

	if (IS_SPECIAL(ch))
	{
	    string[ len++ ] = CSI;
	    string[ len++ ] = K_SECOND(ch);
	    string[ len++ ] = K_THIRD(ch);
	}
	else
	{
	    string[ len++ ] = ch;
	}

	if (len == 1 && ((ch == Ctrl_C && ctrl_c_interrupts)
							  || ch == intr_char))
	{
	    trash_input_buf();
	    got_int = TRUE;
	}

	if (len == 1 && string[0] == CSI)
	{
	    /* Turn CSI into K_CSI. */
	    string[ len++ ] = KS_EXTRA;
	    string[ len++ ] = KE_CSI;
	}

	if (len > 0)
	{
	    add_to_input_buf(string, len);
	    return Pt_CONSUME;
	}
    }

    return Pt_CONTINUE;
}