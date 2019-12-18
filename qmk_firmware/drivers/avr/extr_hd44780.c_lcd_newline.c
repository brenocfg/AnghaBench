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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int LCD_DDRAM ; 
 scalar_t__ LCD_START_LINE1 ; 
 scalar_t__ LCD_START_LINE2 ; 
 scalar_t__ LCD_START_LINE3 ; 
 scalar_t__ LCD_START_LINE4 ; 
 int /*<<< orphan*/  lcd_command (scalar_t__) ; 

__attribute__((used)) static inline void lcd_newline(uint8_t pos) {
    register uint8_t addressCounter;

#if LCD_LINES == 1
    addressCounter = 0;
#endif
#if LCD_LINES == 2
    if (pos < (LCD_START_LINE2))
        addressCounter = LCD_START_LINE2;
    else
        addressCounter = LCD_START_LINE1;
#endif
#if LCD_LINES == 4
#    if KS0073_4LINES_MODE
    if (pos < LCD_START_LINE2)
        addressCounter = LCD_START_LINE2;
    else if ((pos >= LCD_START_LINE2) && (pos < LCD_START_LINE3))
        addressCounter = LCD_START_LINE3;
    else if ((pos >= LCD_START_LINE3) && (pos < LCD_START_LINE4))
        addressCounter = LCD_START_LINE4;
    else
        addressCounter = LCD_START_LINE1;
#    else
    if (pos < LCD_START_LINE3)
        addressCounter = LCD_START_LINE2;
    else if ((pos >= LCD_START_LINE2) && (pos < LCD_START_LINE4))
        addressCounter = LCD_START_LINE3;
    else if ((pos >= LCD_START_LINE3) && (pos < LCD_START_LINE2))
        addressCounter = LCD_START_LINE4;
    else
        addressCounter = LCD_START_LINE1;
#    endif
#endif
    lcd_command((1 << LCD_DDRAM) + addressCounter);

}