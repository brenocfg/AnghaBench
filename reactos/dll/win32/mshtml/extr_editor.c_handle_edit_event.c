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
typedef  int /*<<< orphan*/  nsIDOMKeyEvent ;
typedef  int /*<<< orphan*/  nsIDOMEvent ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  HTMLDocument ;

/* Variables and functions */
#define  DOM_VK_DELETE 160 
#define  DOM_VK_DOWN 159 
#define  DOM_VK_END 158 
#define  DOM_VK_HOME 157 
#define  DOM_VK_LEFT 156 
#define  DOM_VK_RIGHT 155 
#define  DOM_VK_UP 154 
 int /*<<< orphan*/  IID_nsIDOMKeyEvent ; 
#define  NSCMD_BEGINLINE 153 
#define  NSCMD_CHARNEXT 152 
#define  NSCMD_CHARPREVIOUS 151 
#define  NSCMD_DELETECHARFORWARD 150 
#define  NSCMD_DELETEWORDFORWARD 149 
#define  NSCMD_ENDLINE 148 
#define  NSCMD_LINENEXT 147 
#define  NSCMD_LINEPREVIOUS 146 
#define  NSCMD_MOVEBOTTOM 145 
#define  NSCMD_MOVEPAGEDOWN 144 
#define  NSCMD_MOVEPAGEUP 143 
#define  NSCMD_MOVETOP 142 
#define  NSCMD_SELECTBEGINLINE 141 
#define  NSCMD_SELECTBOTTOM 140 
#define  NSCMD_SELECTCHARNEXT 139 
#define  NSCMD_SELECTCHARPREVIOUS 138 
#define  NSCMD_SELECTENDLINE 137 
#define  NSCMD_SELECTLINENEXT 136 
#define  NSCMD_SELECTLINEPREVIOUS 135 
#define  NSCMD_SELECTPAGEDOWN 134 
#define  NSCMD_SELECTPAGEUP 133 
#define  NSCMD_SELECTTOP 132 
#define  NSCMD_SELECTWORDNEXT 131 
#define  NSCMD_SELECTWORDPREVIOUS 130 
#define  NSCMD_WORDNEXT 129 
#define  NSCMD_WORDPREVIOUS 128 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  handle_arrow_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const* const*) ; 
 int /*<<< orphan*/  nsIDOMEvent_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMKeyEvent_GetKeyCode (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nsIDOMKeyEvent_Release (int /*<<< orphan*/ *) ; 

void handle_edit_event(HTMLDocument *This, nsIDOMEvent *event)
{
    nsIDOMKeyEvent *key_event;
    UINT32 code;

    nsIDOMEvent_QueryInterface(event, &IID_nsIDOMKeyEvent, (void**)&key_event);

    nsIDOMKeyEvent_GetKeyCode(key_event, &code);

    switch(code) {
    case DOM_VK_LEFT: {
        static const char * const cmds[] = {
            NSCMD_CHARPREVIOUS,
            NSCMD_WORDPREVIOUS,
            NSCMD_SELECTCHARPREVIOUS,
            NSCMD_SELECTWORDPREVIOUS
        };

        TRACE("left\n");
        handle_arrow_key(This, key_event, cmds);
        break;
    }
    case DOM_VK_RIGHT: {
        static const char * const cmds[] = {
            NSCMD_CHARNEXT,
            NSCMD_WORDNEXT,
            NSCMD_SELECTCHARNEXT,
            NSCMD_SELECTWORDNEXT
        };

        TRACE("right\n");
        handle_arrow_key(This, key_event, cmds);
        break;
    }
    case DOM_VK_UP: {
        static const char * const cmds[] = {
            NSCMD_LINEPREVIOUS,
            NSCMD_MOVEPAGEUP,
            NSCMD_SELECTLINEPREVIOUS,
            NSCMD_SELECTPAGEUP
        };

        TRACE("up\n");
        handle_arrow_key(This, key_event, cmds);
        break;
    }
    case DOM_VK_DOWN: {
        static const char * const cmds[] = {
            NSCMD_LINENEXT,
            NSCMD_MOVEPAGEDOWN,
            NSCMD_SELECTLINENEXT,
            NSCMD_SELECTPAGEDOWN
        };

        TRACE("down\n");
        handle_arrow_key(This, key_event, cmds);
        break;
    }
    case DOM_VK_DELETE: {
        static const char * const cmds[] = {
            NSCMD_DELETECHARFORWARD,
            NSCMD_DELETEWORDFORWARD,
            NULL, NULL
        };

        TRACE("delete\n");
        handle_arrow_key(This, key_event, cmds);
        break;
    }
    case DOM_VK_HOME: {
        static const char * const cmds[] = {
            NSCMD_BEGINLINE,
            NSCMD_MOVETOP,
            NSCMD_SELECTBEGINLINE,
            NSCMD_SELECTTOP
        };

        TRACE("home\n");
        handle_arrow_key(This, key_event, cmds);
        break;
    }
    case DOM_VK_END: {
        static const char * const cmds[] = {
            NSCMD_ENDLINE,
            NSCMD_MOVEBOTTOM,
            NSCMD_SELECTENDLINE,
            NSCMD_SELECTBOTTOM
        };

        TRACE("end\n");
        handle_arrow_key(This, key_event, cmds);
        break;
    }
    }

    nsIDOMKeyEvent_Release(key_event);
}