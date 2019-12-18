#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct vo_x11_state {int has_focus; int win_drag_button1_down; int window_hidden; int pseudo_mapped; int current_icc_screen; int ShmCompletionEvent; int xrandr_event; int /*<<< orphan*/  ShmCompletionWaitCount; int /*<<< orphan*/  pending_vo_events; int /*<<< orphan*/  icc_profile_property; int /*<<< orphan*/  parent; int /*<<< orphan*/  input_ctx; int /*<<< orphan*/  window; int /*<<< orphan*/ * display; int /*<<< orphan*/  fs; int /*<<< orphan*/  compose_status; int /*<<< orphan*/  xic; int /*<<< orphan*/  no_autorepeat; int /*<<< orphan*/  winrc; } ;
struct vo {struct vo_x11_state* x11; } ;
struct bstr {char* member_0; int member_1; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_15__ {int /*<<< orphan*/  atom; } ;
struct TYPE_14__ {int /*<<< orphan*/ * l; } ;
struct TYPE_21__ {TYPE_1__ data; int /*<<< orphan*/  message_type; } ;
struct TYPE_19__ {int button; int /*<<< orphan*/  state; } ;
struct TYPE_18__ {int /*<<< orphan*/  mode; } ;
struct TYPE_17__ {int x_root; int y_root; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_13__ {int /*<<< orphan*/  state; } ;
struct TYPE_16__ {int /*<<< orphan*/  window; } ;
struct TYPE_20__ {int type; TYPE_2__ xproperty; int /*<<< orphan*/  xselection; TYPE_8__ xclient; TYPE_6__ xbutton; TYPE_5__ xcrossing; TYPE_4__ xmotion; TYPE_10__ xkey; TYPE_3__ xconfigure; } ;
typedef  TYPE_7__ XEvent ;
typedef  int /*<<< orphan*/  Status ;
typedef  int /*<<< orphan*/  KeySym ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
#define  ButtonPress 143 
#define  ButtonRelease 142 
#define  ClientMessage 141 
#define  ConfigureNotify 140 
 int /*<<< orphan*/  CurrentTime ; 
#define  DestroyNotify 139 
#define  EnterNotify 138 
#define  Expose 137 
#define  FocusIn 136 
#define  FocusOut 135 
#define  KeyPress 134 
#define  KeyRelease 133 
#define  LeaveNotify 132 
 int MP_INPUT_RELEASE_ALL ; 
 int MP_KEY_CLOSE_WIN ; 
 int /*<<< orphan*/  MP_KEY_MOUSE_BTN_COUNT ; 
 int MP_KEY_MOUSE_ENTER ; 
 int MP_KEY_MOUSE_LEAVE ; 
 int MP_KEY_STATE_DOWN ; 
 int MP_KEY_STATE_UP ; 
 int MP_MBTN_BASE ; 
 int /*<<< orphan*/  MP_TRACE (struct vo_x11_state*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo_x11_state*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct vo_x11_state*,char*) ; 
#define  MapNotify 131 
#define  MotionNotify 130 
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  NotifyNormal ; 
#define  PropertyNotify 129 
 int /*<<< orphan*/  RC_H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC_W (int /*<<< orphan*/ ) ; 
#define  SelectionNotify 128 
 int /*<<< orphan*/  VO_EVENT_EXPOSE ; 
 int /*<<< orphan*/  VO_EVENT_ICC_PROFILE_CHANGED ; 
 int /*<<< orphan*/  VO_EVENT_WIN_STATE ; 
 int /*<<< orphan*/  WM_DELETE_WINDOW ; 
 int /*<<< orphan*/  WM_PROTOCOLS ; 
 int /*<<< orphan*/  WM_STATE ; 
 int /*<<< orphan*/  XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 long XEMBED_REQUEST_FOCUS ; 
 int /*<<< orphan*/  XLookupBoth ; 
 int /*<<< orphan*/  XLookupChars ; 
 int /*<<< orphan*/  XLookupString (TYPE_10__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMoveResizeWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ XPending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XUngrabPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Xutf8LookupString (int /*<<< orphan*/ ,TYPE_10__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _NET_FRAME_EXTENTS ; 
 int /*<<< orphan*/  _NET_WM_STATE ; 
 int get_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_input_put_key_utf8 (int /*<<< orphan*/ ,int,struct bstr) ; 
 int /*<<< orphan*/  mp_input_set_mouse_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_input_test_dragging (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_all_keys (struct vo*) ; 
 int /*<<< orphan*/  update_vo_size (struct vo*) ; 
 int /*<<< orphan*/  vo_update_cursor (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_check_net_wm_state_fullscreen_change (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_dnd_handle_message (struct vo*,TYPE_8__*) ; 
 int /*<<< orphan*/  vo_x11_dnd_handle_selection (struct vo*,int /*<<< orphan*/ *) ; 
 int vo_x11_lookupkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_x11_update_geometry (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_xembed_handle_message (struct vo*,TYPE_8__*) ; 
 int /*<<< orphan*/  vo_x11_xembed_send_message (struct vo_x11_state*,long*) ; 
 int /*<<< orphan*/  x11_send_ewmh_msg (struct vo_x11_state*,char*,long*) ; 
 int /*<<< orphan*/  xrandr_read (struct vo_x11_state*) ; 
 int /*<<< orphan*/  xscreensaver_heartbeat (struct vo_x11_state*) ; 

void vo_x11_check_events(struct vo *vo)
{
    struct vo_x11_state *x11 = vo->x11;
    Display *display = vo->x11->display;
    XEvent Event;

    xscreensaver_heartbeat(vo->x11);

    while (XPending(display)) {
        XNextEvent(display, &Event);
        MP_TRACE(x11, "XEvent: %d\n", Event.type);
        switch (Event.type) {
        case Expose:
            x11->pending_vo_events |= VO_EVENT_EXPOSE;
            break;
        case ConfigureNotify:
            if (x11->window == None)
                break;
            vo_x11_update_geometry(vo);
            if (x11->parent && Event.xconfigure.window == x11->parent) {
                MP_TRACE(x11, "adjusting embedded window position\n");
                XMoveResizeWindow(x11->display, x11->window,
                                  0, 0, RC_W(x11->winrc), RC_H(x11->winrc));
            }
            break;
        case KeyPress: {
            char buf[100];
            KeySym keySym = 0;
            int modifiers = get_mods(Event.xkey.state);
            if (x11->no_autorepeat)
                modifiers |= MP_KEY_STATE_DOWN;
            if (x11->xic) {
                Status status;
                int len = Xutf8LookupString(x11->xic, &Event.xkey, buf,
                                            sizeof(buf), &keySym, &status);
                int mpkey = vo_x11_lookupkey(keySym);
                if (mpkey) {
                    mp_input_put_key(x11->input_ctx, mpkey | modifiers);
                } else if (status == XLookupChars || status == XLookupBoth) {
                    struct bstr t = { buf, len };
                    mp_input_put_key_utf8(x11->input_ctx, modifiers, t);
                }
            } else {
                XLookupString(&Event.xkey, buf, sizeof(buf), &keySym,
                              &x11->compose_status);
                int mpkey = vo_x11_lookupkey(keySym);
                if (mpkey)
                    mp_input_put_key(x11->input_ctx, mpkey | modifiers);
            }
            break;
        }
        case FocusIn:
            x11->has_focus = true;
            vo_update_cursor(vo);
            break;
        case FocusOut:
            release_all_keys(vo);
            x11->has_focus = false;
            vo_update_cursor(vo);
            break;
        case KeyRelease:
            release_all_keys(vo);
            break;
        case MotionNotify:
            if (x11->win_drag_button1_down && !x11->fs &&
                !mp_input_test_dragging(x11->input_ctx, Event.xmotion.x,
                                                        Event.xmotion.y))
            {
                mp_input_put_key(x11->input_ctx, MP_INPUT_RELEASE_ALL);
                XUngrabPointer(x11->display, CurrentTime);

                long params[5] = {
                    Event.xmotion.x_root, Event.xmotion.y_root,
                    8, // _NET_WM_MOVERESIZE_MOVE
                    1, // button 1
                    1, // source indication: normal
                };
                x11_send_ewmh_msg(x11, "_NET_WM_MOVERESIZE", params);
            } else {
                mp_input_set_mouse_pos(x11->input_ctx, Event.xmotion.x,
                                                       Event.xmotion.y);
            }
            x11->win_drag_button1_down = false;
            break;
        case LeaveNotify:
            if (Event.xcrossing.mode != NotifyNormal)
                break;
            x11->win_drag_button1_down = false;
            mp_input_put_key(x11->input_ctx, MP_KEY_MOUSE_LEAVE);
            break;
        case EnterNotify:
            if (Event.xcrossing.mode != NotifyNormal)
                break;
            mp_input_put_key(x11->input_ctx, MP_KEY_MOUSE_ENTER);
            break;
        case ButtonPress:
            if (Event.xbutton.button - 1 >= MP_KEY_MOUSE_BTN_COUNT)
                break;
            if (Event.xbutton.button == 1)
                x11->win_drag_button1_down = true;
            mp_input_put_key(x11->input_ctx,
                             (MP_MBTN_BASE + Event.xbutton.button - 1) |
                             get_mods(Event.xbutton.state) | MP_KEY_STATE_DOWN);
            long msg[4] = {XEMBED_REQUEST_FOCUS};
            vo_x11_xembed_send_message(x11, msg);
            break;
        case ButtonRelease:
            if (Event.xbutton.button - 1 >= MP_KEY_MOUSE_BTN_COUNT)
                break;
            if (Event.xbutton.button == 1)
                x11->win_drag_button1_down = false;
            mp_input_put_key(x11->input_ctx,
                             (MP_MBTN_BASE + Event.xbutton.button - 1) |
                             get_mods(Event.xbutton.state) | MP_KEY_STATE_UP);
            break;
        case MapNotify:
            x11->window_hidden = false;
            x11->pseudo_mapped = true;
            x11->current_icc_screen = -1;
            vo_x11_update_geometry(vo);
            break;
        case DestroyNotify:
            MP_WARN(x11, "Our window was destroyed, exiting\n");
            mp_input_put_key(x11->input_ctx, MP_KEY_CLOSE_WIN);
            x11->window = 0;
            break;
        case ClientMessage:
            if (Event.xclient.message_type == XA(x11, WM_PROTOCOLS) &&
                Event.xclient.data.l[0] == XA(x11, WM_DELETE_WINDOW))
                mp_input_put_key(x11->input_ctx, MP_KEY_CLOSE_WIN);
            vo_x11_dnd_handle_message(vo, &Event.xclient);
            vo_x11_xembed_handle_message(vo, &Event.xclient);
            break;
        case SelectionNotify:
            vo_x11_dnd_handle_selection(vo, &Event.xselection);
            break;
        case PropertyNotify:
            if (Event.xproperty.atom == XA(x11, _NET_FRAME_EXTENTS) ||
                Event.xproperty.atom == XA(x11, WM_STATE))
            {
                if (!x11->pseudo_mapped && !x11->parent) {
                    MP_VERBOSE(x11, "not waiting for MapNotify\n");
                    x11->pseudo_mapped = true;
                }
            } else if (Event.xproperty.atom == XA(x11, _NET_WM_STATE)) {
                x11->pending_vo_events |= VO_EVENT_WIN_STATE;
                vo_x11_check_net_wm_state_fullscreen_change(vo);
            } else if (Event.xproperty.atom == x11->icc_profile_property) {
                x11->pending_vo_events |= VO_EVENT_ICC_PROFILE_CHANGED;
            }
            break;
        default:
            if (Event.type == x11->ShmCompletionEvent) {
                if (x11->ShmCompletionWaitCount > 0)
                    x11->ShmCompletionWaitCount--;
            }
            if (Event.type == x11->xrandr_event) {
                xrandr_read(x11);
                vo_x11_update_geometry(vo);
            }
            break;
        }
    }

    update_vo_size(vo);
}