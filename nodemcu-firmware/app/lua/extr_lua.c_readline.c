#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t line_position; char* line; int done; int len; int /*<<< orphan*/  prmt; } ;
typedef  TYPE_1__ lua_Load ;

/* Variables and functions */
 scalar_t__ end_char ; 
 char last_nl_char ; 
 size_t need_len ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 scalar_t__ run_input ; 
 scalar_t__ uart0_echo ; 
 scalar_t__ uart_getc (char*) ; 
 int /*<<< orphan*/  uart_on_data_cb (char*,size_t) ; 
 int /*<<< orphan*/  uart_putc (char) ; 

__attribute__((used)) static bool readline(lua_Load *load){
  // NODE_DBG("readline() is called.\n");
  bool need_dojob = false;
  char ch;
  while (uart_getc(&ch))
  {
    if(run_input)
    {
      char tmp_last_nl_char = last_nl_char;
      // reset marker, will be finally set below when newline is processed
      last_nl_char = '\0';

      /* handle CR & LF characters
         filters second char of LF&CR (\n\r) or CR&LF (\r\n) sequences */
      if ((ch == '\r' && tmp_last_nl_char == '\n') || // \n\r sequence -> skip \r
          (ch == '\n' && tmp_last_nl_char == '\r'))   // \r\n sequence -> skip \n
      {
        continue;
      }

      /* backspace key */
      else if (ch == 0x7f || ch == 0x08)
      {
        if (load->line_position > 0)
        {
          if(uart0_echo) uart_putc(0x08);
          if(uart0_echo) uart_putc(' ');
          if(uart0_echo) uart_putc(0x08);
          load->line_position--;
        }
        load->line[load->line_position] = 0;
        continue;
      }
      /* EOT(ctrl+d) */
      // else if (ch == 0x04)
      // {
      //   if (load->line_position == 0)
      //     // No input which makes lua interpreter close
      //     donejob(load);
      //   else
      //     continue;
      // }

      /* end of line */
      if (ch == '\r' || ch == '\n')
      {
        last_nl_char = ch;

        load->line[load->line_position] = 0;
        if(uart0_echo) uart_putc('\n');
        uart_on_data_cb(load->line, load->line_position);
        if (load->line_position == 0)
        {
          /* Get a empty line, then go to get a new line */
          puts(load->prmt);
          continue;
        } else {
          load->done = 1;
          need_dojob = true;
          break;
        }
      }

      /* other control character or not an acsii character */
      // if (ch < 0x20 || ch >= 0x80)
      // {
      //   continue;
      // }

      /* echo */
      if(uart0_echo) uart_putc(ch);

          /* it's a large line, discard it */
      if ( load->line_position + 1 >= load->len ){
        load->line_position = 0;
      }
    }

    load->line[load->line_position] = ch;
    load->line_position++;

    if(!run_input)
    {
      if( ((need_len!=0) && (load->line_position >= need_len)) || \
        (load->line_position >= load->len) || \
        ((end_char>=0) && ((unsigned char)ch==(unsigned char)end_char)) )
      {
        uart_on_data_cb(load->line, load->line_position);
        load->line_position = 0;
      }
    }

    ch = 0;
  }

  if( (load->line_position > 0) && (!run_input) && (need_len==0) && (end_char<0) )
  {
    uart_on_data_cb(load->line, load->line_position);
    load->line_position = 0;
  }

  return need_dojob;
}