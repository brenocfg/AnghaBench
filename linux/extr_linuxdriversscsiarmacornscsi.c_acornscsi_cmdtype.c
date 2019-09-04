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
typedef  int /*<<< orphan*/  cmdtype_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MISC ; 
 int /*<<< orphan*/  CMD_READ ; 
 int /*<<< orphan*/  CMD_WRITE ; 
#define  READ_10 133 
#define  READ_12 132 
#define  READ_6 131 
#define  WRITE_10 130 
#define  WRITE_12 129 
#define  WRITE_6 128 

__attribute__((used)) static inline
cmdtype_t acornscsi_cmdtype(int command)
{
    switch (command) {
    case WRITE_6:  case WRITE_10:  case WRITE_12:
	return CMD_WRITE;
    case READ_6:   case READ_10:   case READ_12:
	return CMD_READ;
    default:
	return CMD_MISC;
    }
}