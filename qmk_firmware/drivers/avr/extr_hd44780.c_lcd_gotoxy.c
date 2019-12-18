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
typedef  int uint8_t ;

/* Variables and functions */
 int LCD_DDRAM ; 
 int LCD_START_LINE1 ; 
 int LCD_START_LINE2 ; 
 int LCD_START_LINE3 ; 
 int LCD_START_LINE4 ; 
 int /*<<< orphan*/  lcd_command (int) ; 

void lcd_gotoxy(uint8_t x, uint8_t y) {
#if LCD_LINES == 1
    lcd_command((1 << LCD_DDRAM) + LCD_START_LINE1 + x);
#endif
#if LCD_LINES == 2
    if (y == 0)
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE1 + x);
    else
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE2 + x);
#endif
#if LCD_LINES == 4
    if (y == 0)
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE1 + x);
    else if (y == 1)
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE2 + x);
    else if (y == 2)
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE3 + x);
    else /* y==3 */
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE4 + x);
#endif

}