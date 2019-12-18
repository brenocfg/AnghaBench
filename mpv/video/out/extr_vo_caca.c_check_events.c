#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vo {int /*<<< orphan*/  input_ctx; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  dither_color; int /*<<< orphan*/  dither; int /*<<< orphan*/  dither_charset; int /*<<< orphan*/  dither_antialias; int /*<<< orphan*/  dither_algo; int /*<<< orphan*/  display; } ;
struct TYPE_7__ {int ch; } ;
struct TYPE_6__ {scalar_t__ button; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_2__ key; TYPE_1__ mouse; } ;
struct TYPE_9__ {int type; TYPE_3__ data; } ;
typedef  TYPE_4__ caca_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACA_EVENT_ANY ; 
#define  CACA_EVENT_KEY_PRESS 133 
#define  CACA_EVENT_MOUSE_MOTION 132 
#define  CACA_EVENT_MOUSE_PRESS 131 
#define  CACA_EVENT_MOUSE_RELEASE 130 
#define  CACA_EVENT_QUIT 129 
#define  CACA_EVENT_RESIZE 128 
 int MP_KEY_CLOSE_WIN ; 
 int MP_KEY_STATE_DOWN ; 
 int MP_KEY_STATE_UP ; 
 scalar_t__ MP_MBTN_BASE ; 
 int /*<<< orphan*/  caca_get_dither_algorithm_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_get_dither_antialias_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_get_dither_charset_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_get_dither_color_list (int /*<<< orphan*/ ) ; 
 scalar_t__ caca_get_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_refresh_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_set_dither_algorithm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_set_dither_antialias (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_set_dither_charset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_set_dither_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keysym_map ; 
 int lookup_keymap_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_input_set_mouse_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resize (struct vo*) ; 
 int /*<<< orphan*/  set_next_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static void check_events(struct vo *vo)
{
    struct priv *priv = vo->priv;

    caca_event_t cev;
    while (caca_get_event(priv->display, CACA_EVENT_ANY, &cev, 0)) {

        switch (cev.type) {
        case CACA_EVENT_RESIZE:
            caca_refresh_display(priv->display);
            resize(vo);
            break;
        case CACA_EVENT_QUIT:
            mp_input_put_key(vo->input_ctx, MP_KEY_CLOSE_WIN);
            break;
        case CACA_EVENT_MOUSE_MOTION:
            mp_input_set_mouse_pos(vo->input_ctx, cev.data.mouse.x, cev.data.mouse.y);
            break;
        case CACA_EVENT_MOUSE_PRESS:
            mp_input_put_key(vo->input_ctx,
                    (MP_MBTN_BASE + cev.data.mouse.button - 1) | MP_KEY_STATE_DOWN);
            break;
        case CACA_EVENT_MOUSE_RELEASE:
            mp_input_put_key(vo->input_ctx,
                    (MP_MBTN_BASE + cev.data.mouse.button - 1) | MP_KEY_STATE_UP);
            break;
        case CACA_EVENT_KEY_PRESS:
        {
            int key = cev.data.key.ch;
            int mpkey = lookup_keymap_table(keysym_map, key);
            const char *msg_name;

            if (mpkey)
                mp_input_put_key(vo->input_ctx, mpkey);
            else
            switch (key) {
            case 'd':
            case 'D':
                /* Toggle dithering algorithm */
                set_next_str(caca_get_dither_algorithm_list(priv->dither),
                             &priv->dither_algo, &msg_name);
                caca_set_dither_algorithm(priv->dither, priv->dither_algo);
                break;

            case 'a':
            case 'A':
                /* Toggle antialiasing method */
                set_next_str(caca_get_dither_antialias_list(priv->dither),
                             &priv->dither_antialias, &msg_name);
                caca_set_dither_antialias(priv->dither, priv->dither_antialias);
                break;

            case 'h':
            case 'H':
                /* Toggle charset method */
                set_next_str(caca_get_dither_charset_list(priv->dither),
                             &priv->dither_charset, &msg_name);
                caca_set_dither_charset(priv->dither, priv->dither_charset);
                break;

            case 'c':
            case 'C':
                /* Toggle color method */
                set_next_str(caca_get_dither_color_list(priv->dither),
                             &priv->dither_color, &msg_name);
                caca_set_dither_color(priv->dither, priv->dither_color);
                break;

            default:
                if (key <= 255)
                    mp_input_put_key(vo->input_ctx, key);
                break;
            }
        }
        }
    }
}