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
 int CONST_CS ; 
 int CONST_PERSISTENT ; 
 int /*<<< orphan*/  REGISTER_MAIN_LONG_CONSTANT (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UPLOAD_ERROR_A ; 
 int /*<<< orphan*/  UPLOAD_ERROR_B ; 
 int /*<<< orphan*/  UPLOAD_ERROR_C ; 
 int /*<<< orphan*/  UPLOAD_ERROR_D ; 
 int /*<<< orphan*/  UPLOAD_ERROR_E ; 
 int /*<<< orphan*/  UPLOAD_ERROR_F ; 
 int /*<<< orphan*/  UPLOAD_ERROR_OK ; 
 int /*<<< orphan*/  UPLOAD_ERROR_X ; 

void php_rfc1867_register_constants(void) /* {{{ */
{
	REGISTER_MAIN_LONG_CONSTANT("UPLOAD_ERR_OK",         UPLOAD_ERROR_OK, CONST_CS | CONST_PERSISTENT);
	REGISTER_MAIN_LONG_CONSTANT("UPLOAD_ERR_INI_SIZE",   UPLOAD_ERROR_A,  CONST_CS | CONST_PERSISTENT);
	REGISTER_MAIN_LONG_CONSTANT("UPLOAD_ERR_FORM_SIZE",  UPLOAD_ERROR_B,  CONST_CS | CONST_PERSISTENT);
	REGISTER_MAIN_LONG_CONSTANT("UPLOAD_ERR_PARTIAL",    UPLOAD_ERROR_C,  CONST_CS | CONST_PERSISTENT);
	REGISTER_MAIN_LONG_CONSTANT("UPLOAD_ERR_NO_FILE",    UPLOAD_ERROR_D,  CONST_CS | CONST_PERSISTENT);
	REGISTER_MAIN_LONG_CONSTANT("UPLOAD_ERR_NO_TMP_DIR", UPLOAD_ERROR_E,  CONST_CS | CONST_PERSISTENT);
	REGISTER_MAIN_LONG_CONSTANT("UPLOAD_ERR_CANT_WRITE", UPLOAD_ERROR_F,  CONST_CS | CONST_PERSISTENT);
	REGISTER_MAIN_LONG_CONSTANT("UPLOAD_ERR_EXTENSION",  UPLOAD_ERROR_X,  CONST_CS | CONST_PERSISTENT);
}