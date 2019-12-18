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
typedef  int php_json_error_code ;

/* Variables and functions */
#define  PHP_JSON_ERROR_CTRL_CHAR 138 
#define  PHP_JSON_ERROR_DEPTH 137 
#define  PHP_JSON_ERROR_INF_OR_NAN 136 
#define  PHP_JSON_ERROR_INVALID_PROPERTY_NAME 135 
#define  PHP_JSON_ERROR_NONE 134 
#define  PHP_JSON_ERROR_RECURSION 133 
#define  PHP_JSON_ERROR_STATE_MISMATCH 132 
#define  PHP_JSON_ERROR_SYNTAX 131 
#define  PHP_JSON_ERROR_UNSUPPORTED_TYPE 130 
#define  PHP_JSON_ERROR_UTF16 129 
#define  PHP_JSON_ERROR_UTF8 128 

__attribute__((used)) static const char *php_json_get_error_msg(php_json_error_code error_code) /* {{{ */
{
	switch(error_code) {
		case PHP_JSON_ERROR_NONE:
			return "No error";
		case PHP_JSON_ERROR_DEPTH:
			return "Maximum stack depth exceeded";
		case PHP_JSON_ERROR_STATE_MISMATCH:
			return "State mismatch (invalid or malformed JSON)";
		case PHP_JSON_ERROR_CTRL_CHAR:
			return "Control character error, possibly incorrectly encoded";
		case PHP_JSON_ERROR_SYNTAX:
			return "Syntax error";
		case PHP_JSON_ERROR_UTF8:
			return "Malformed UTF-8 characters, possibly incorrectly encoded";
		case PHP_JSON_ERROR_RECURSION:
			return "Recursion detected";
		case PHP_JSON_ERROR_INF_OR_NAN:
			return "Inf and NaN cannot be JSON encoded";
		case PHP_JSON_ERROR_UNSUPPORTED_TYPE:
			return "Type is not supported";
		case PHP_JSON_ERROR_INVALID_PROPERTY_NAME:
			return "The decoded property name is invalid";
		case PHP_JSON_ERROR_UTF16:
			return "Single unpaired UTF-16 surrogate in unicode escape";
		default:
			return "Unknown error";
	}
}