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
typedef  int uint32_t ;
struct TYPE_2__ {int baut_rate; void* exist_parity; int /*<<< orphan*/  parity; int /*<<< orphan*/  stop_bits; void* data_bits; } ;

/* Variables and functions */
#define  BIT_RATE_115200 149 
#define  BIT_RATE_1200 148 
#define  BIT_RATE_1843200 147 
#define  BIT_RATE_19200 146 
#define  BIT_RATE_230400 145 
#define  BIT_RATE_2400 144 
#define  BIT_RATE_256000 143 
#define  BIT_RATE_300 142 
#define  BIT_RATE_31250 141 
#define  BIT_RATE_3686400 140 
#define  BIT_RATE_38400 139 
#define  BIT_RATE_460800 138 
#define  BIT_RATE_4800 137 
#define  BIT_RATE_57600 136 
#define  BIT_RATE_600 135 
#define  BIT_RATE_74880 134 
#define  BIT_RATE_921600 133 
#define  BIT_RATE_9600 132 
 void* EIGHT_BITS ; 
 int /*<<< orphan*/  EVEN_BITS ; 
 void* FIVE_BITS ; 
 int /*<<< orphan*/  NONE_BITS ; 
 int /*<<< orphan*/  ODD_BITS ; 
 int /*<<< orphan*/  ONE_HALF_STOP_BIT ; 
 int /*<<< orphan*/  ONE_STOP_BIT ; 
#define  PLATFORM_UART_PARITY_EVEN 131 
#define  PLATFORM_UART_PARITY_ODD 130 
#define  PLATFORM_UART_STOPBITS_1_5 129 
#define  PLATFORM_UART_STOPBITS_2 128 
 void* SEVEN_BITS ; 
 void* SIX_BITS ; 
 void* STICK_PARITY_DIS ; 
 void* STICK_PARITY_EN ; 
 int /*<<< orphan*/  TWO_STOP_BIT ; 
 TYPE_1__ UartDev ; 
 int /*<<< orphan*/  uart_setup (unsigned int) ; 

uint32_t platform_uart_setup( unsigned id, uint32_t baud, int databits, int parity, int stopbits )
{
  switch( baud )
  {
    case BIT_RATE_300:
    case BIT_RATE_600:
    case BIT_RATE_1200:
    case BIT_RATE_2400:
    case BIT_RATE_4800:
    case BIT_RATE_9600:
    case BIT_RATE_19200:
    case BIT_RATE_31250:
    case BIT_RATE_38400:
    case BIT_RATE_57600:
    case BIT_RATE_74880:
    case BIT_RATE_115200:
    case BIT_RATE_230400:
    case BIT_RATE_256000:
    case BIT_RATE_460800:
    case BIT_RATE_921600:
    case BIT_RATE_1843200:
    case BIT_RATE_3686400:
      UartDev.baut_rate = baud;
      break;
    default:
      UartDev.baut_rate = BIT_RATE_9600;
      break;
  }

  switch( databits )
  {
    case 5:
      UartDev.data_bits = FIVE_BITS;
      break;
    case 6:
      UartDev.data_bits = SIX_BITS;
      break;
    case 7:
      UartDev.data_bits = SEVEN_BITS;
      break;
    case 8:
      UartDev.data_bits = EIGHT_BITS;
      break;
    default:
      UartDev.data_bits = EIGHT_BITS;
      break;
  }

  switch (stopbits)
  {
    case PLATFORM_UART_STOPBITS_1_5:
      UartDev.stop_bits = ONE_HALF_STOP_BIT;
      break;
    case PLATFORM_UART_STOPBITS_2:
      UartDev.stop_bits = TWO_STOP_BIT;
      break;
    default:
      UartDev.stop_bits = ONE_STOP_BIT;
      break;
  }

  switch (parity)
  {
    case PLATFORM_UART_PARITY_EVEN:
      UartDev.parity = EVEN_BITS;
      UartDev.exist_parity = STICK_PARITY_EN;
      break;
    case PLATFORM_UART_PARITY_ODD:
      UartDev.parity = ODD_BITS;
      UartDev.exist_parity = STICK_PARITY_EN;
      break;
    default:
      UartDev.parity = NONE_BITS;
      UartDev.exist_parity = STICK_PARITY_DIS;
      break;
  }

  uart_setup(id);

  return baud;
}