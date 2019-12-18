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

/* Variables and functions */
#define  SPI_ERROR_ARGUMENT 155 
#define  SPI_ERROR_CONNECT 154 
#define  SPI_ERROR_COPY 153 
#define  SPI_ERROR_NOATTRIBUTE 152 
#define  SPI_ERROR_NOOUTFUNC 151 
#define  SPI_ERROR_OPUNKNOWN 150 
#define  SPI_ERROR_PARAM 149 
#define  SPI_ERROR_REL_DUPLICATE 148 
#define  SPI_ERROR_REL_NOT_FOUND 147 
#define  SPI_ERROR_TRANSACTION 146 
#define  SPI_ERROR_TYPUNKNOWN 145 
#define  SPI_ERROR_UNCONNECTED 144 
#define  SPI_OK_CONNECT 143 
#define  SPI_OK_CURSOR 142 
#define  SPI_OK_DELETE 141 
#define  SPI_OK_DELETE_RETURNING 140 
#define  SPI_OK_FETCH 139 
#define  SPI_OK_FINISH 138 
#define  SPI_OK_INSERT 137 
#define  SPI_OK_INSERT_RETURNING 136 
#define  SPI_OK_REL_REGISTER 135 
#define  SPI_OK_REL_UNREGISTER 134 
#define  SPI_OK_REWRITTEN 133 
#define  SPI_OK_SELECT 132 
#define  SPI_OK_SELINTO 131 
#define  SPI_OK_UPDATE 130 
#define  SPI_OK_UPDATE_RETURNING 129 
#define  SPI_OK_UTILITY 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
SPI_result_code_string(int code)
{
	static char buf[64];

	switch (code)
	{
		case SPI_ERROR_CONNECT:
			return "SPI_ERROR_CONNECT";
		case SPI_ERROR_COPY:
			return "SPI_ERROR_COPY";
		case SPI_ERROR_OPUNKNOWN:
			return "SPI_ERROR_OPUNKNOWN";
		case SPI_ERROR_UNCONNECTED:
			return "SPI_ERROR_UNCONNECTED";
		case SPI_ERROR_ARGUMENT:
			return "SPI_ERROR_ARGUMENT";
		case SPI_ERROR_PARAM:
			return "SPI_ERROR_PARAM";
		case SPI_ERROR_TRANSACTION:
			return "SPI_ERROR_TRANSACTION";
		case SPI_ERROR_NOATTRIBUTE:
			return "SPI_ERROR_NOATTRIBUTE";
		case SPI_ERROR_NOOUTFUNC:
			return "SPI_ERROR_NOOUTFUNC";
		case SPI_ERROR_TYPUNKNOWN:
			return "SPI_ERROR_TYPUNKNOWN";
		case SPI_ERROR_REL_DUPLICATE:
			return "SPI_ERROR_REL_DUPLICATE";
		case SPI_ERROR_REL_NOT_FOUND:
			return "SPI_ERROR_REL_NOT_FOUND";
		case SPI_OK_CONNECT:
			return "SPI_OK_CONNECT";
		case SPI_OK_FINISH:
			return "SPI_OK_FINISH";
		case SPI_OK_FETCH:
			return "SPI_OK_FETCH";
		case SPI_OK_UTILITY:
			return "SPI_OK_UTILITY";
		case SPI_OK_SELECT:
			return "SPI_OK_SELECT";
		case SPI_OK_SELINTO:
			return "SPI_OK_SELINTO";
		case SPI_OK_INSERT:
			return "SPI_OK_INSERT";
		case SPI_OK_DELETE:
			return "SPI_OK_DELETE";
		case SPI_OK_UPDATE:
			return "SPI_OK_UPDATE";
		case SPI_OK_CURSOR:
			return "SPI_OK_CURSOR";
		case SPI_OK_INSERT_RETURNING:
			return "SPI_OK_INSERT_RETURNING";
		case SPI_OK_DELETE_RETURNING:
			return "SPI_OK_DELETE_RETURNING";
		case SPI_OK_UPDATE_RETURNING:
			return "SPI_OK_UPDATE_RETURNING";
		case SPI_OK_REWRITTEN:
			return "SPI_OK_REWRITTEN";
		case SPI_OK_REL_REGISTER:
			return "SPI_OK_REL_REGISTER";
		case SPI_OK_REL_UNREGISTER:
			return "SPI_OK_REL_UNREGISTER";
	}
	/* Unrecognized code ... return something useful ... */
	sprintf(buf, "Unrecognized SPI code %d", code);
	return buf;
}