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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,char*) ; 
 int /*<<< orphan*/  PSH_RTLREADING ; 
 int /*<<< orphan*/  PSH_STRETCHWATERMARK ; 
 int /*<<< orphan*/  PSH_USEPAGELANG ; 
 int /*<<< orphan*/  add_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID PROPSHEET_UnImplementedFlags(DWORD dwFlags)
{
    CHAR string[256];

    string[0] = '\0';

  /*
   * unhandled header flags:
   *  PSH_RTLREADING         0x00000800
   *  PSH_STRETCHWATERMARK   0x00040000
   *  PSH_USEPAGELANG        0x00200000
   */

    add_flag(PSH_RTLREADING);
    add_flag(PSH_STRETCHWATERMARK);
    add_flag(PSH_USEPAGELANG);
    if (string[0] != '\0')
	FIXME("%s\n", string);
}