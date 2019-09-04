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
struct TYPE_6__ {char AsciiChar; } ;
struct TYPE_7__ {int /*<<< orphan*/  wVirtualKeyCode; TYPE_1__ uChar; int /*<<< orphan*/  bKeyDown; } ;
struct TYPE_8__ {TYPE_2__ KeyEvent; } ;
struct TYPE_9__ {scalar_t__ EventType; TYPE_3__ Event; } ;
typedef  TYPE_4__ INPUT_RECORD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int CHAR_CTRL_C ; 
 scalar_t__ KEY_EVENT ; 
 int /*<<< orphan*/  ReadConsoleInput (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assure_stdin_handle () ; 
 int esc_seq_chr () ; 
 int esc_seq_process_vk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  std_in ; 

int mp_hal_stdin_rx_chr(void) {
    // currently processing escape seq?
    const int ret = esc_seq_chr();
    if (ret) {
        return ret;
    }

    // poll until key which we handle is pressed
    assure_stdin_handle();
    DWORD num_read;
    INPUT_RECORD rec;
    for (;;) {
      if (!ReadConsoleInput(std_in, &rec, 1, &num_read) || !num_read) {
          return CHAR_CTRL_C; // EOF, ctrl-D
      }
      if (rec.EventType != KEY_EVENT || !rec.Event.KeyEvent.bKeyDown) { // only want key down events
          continue;
      }
      const char c = rec.Event.KeyEvent.uChar.AsciiChar;
      if (c) { // plain ascii char, return it
          return c;
      }
      const int ret = esc_seq_process_vk(rec.Event.KeyEvent.wVirtualKeyCode);
      if (ret) {
          return ret;
      }
    }
}