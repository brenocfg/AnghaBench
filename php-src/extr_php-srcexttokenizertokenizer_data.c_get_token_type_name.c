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
#define  T_ABSTRACT 261 
#define  T_AND_EQUAL 260 
#define  T_ARRAY 259 
#define  T_ARRAY_CAST 258 
#define  T_AS 257 
#define  T_BOOLEAN_AND 256 
#define  T_BOOLEAN_OR 255 
#define  T_BOOL_CAST 254 
#define  T_BREAK 253 
#define  T_CALLABLE 252 
#define  T_CASE 251 
#define  T_CATCH 250 
#define  T_CLASS 249 
#define  T_CLASS_C 248 
#define  T_CLONE 247 
#define  T_CLOSE_TAG 246 
#define  T_COALESCE 245 
#define  T_COALESCE_EQUAL 244 
#define  T_COMMENT 243 
#define  T_CONCAT_EQUAL 242 
#define  T_CONST 241 
#define  T_CONSTANT_ENCAPSED_STRING 240 
#define  T_CONTINUE 239 
#define  T_CURLY_OPEN 238 
#define  T_DEC 237 
#define  T_DECLARE 236 
#define  T_DEFAULT 235 
#define  T_DIR 234 
#define  T_DIV_EQUAL 233 
#define  T_DNUMBER 232 
#define  T_DO 231 
#define  T_DOC_COMMENT 230 
#define  T_DOLLAR_OPEN_CURLY_BRACES 229 
#define  T_DOUBLE_ARROW 228 
#define  T_DOUBLE_CAST 227 
#define  T_ECHO 226 
#define  T_ELLIPSIS 225 
#define  T_ELSE 224 
#define  T_ELSEIF 223 
#define  T_EMPTY 222 
#define  T_ENCAPSED_AND_WHITESPACE 221 
#define  T_ENDDECLARE 220 
#define  T_ENDFOR 219 
#define  T_ENDFOREACH 218 
#define  T_ENDIF 217 
#define  T_ENDSWITCH 216 
#define  T_ENDWHILE 215 
#define  T_END_HEREDOC 214 
#define  T_EVAL 213 
#define  T_EXIT 212 
#define  T_EXTENDS 211 
#define  T_FILE 210 
#define  T_FINAL 209 
#define  T_FINALLY 208 
#define  T_FOR 207 
#define  T_FOREACH 206 
#define  T_FUNCTION 205 
#define  T_FUNC_C 204 
#define  T_GLOBAL 203 
#define  T_GOTO 202 
#define  T_HALT_COMPILER 201 
#define  T_IF 200 
#define  T_IMPLEMENTS 199 
#define  T_INC 198 
#define  T_INCLUDE 197 
#define  T_INCLUDE_ONCE 196 
#define  T_INLINE_HTML 195 
#define  T_INSTANCEOF 194 
#define  T_INSTEADOF 193 
#define  T_INTERFACE 192 
#define  T_INT_CAST 191 
#define  T_ISSET 190 
#define  T_IS_EQUAL 189 
#define  T_IS_GREATER_OR_EQUAL 188 
#define  T_IS_IDENTICAL 187 
#define  T_IS_NOT_EQUAL 186 
#define  T_IS_NOT_IDENTICAL 185 
#define  T_IS_SMALLER_OR_EQUAL 184 
#define  T_LINE 183 
#define  T_LIST 182 
#define  T_LNUMBER 181 
#define  T_LOGICAL_AND 180 
#define  T_LOGICAL_OR 179 
#define  T_LOGICAL_XOR 178 
#define  T_METHOD_C 177 
#define  T_MINUS_EQUAL 176 
#define  T_MOD_EQUAL 175 
#define  T_MUL_EQUAL 174 
#define  T_NAMESPACE 173 
#define  T_NEW 172 
#define  T_NS_C 171 
#define  T_NS_SEPARATOR 170 
#define  T_NUM_STRING 169 
#define  T_OBJECT_CAST 168 
#define  T_OBJECT_OPERATOR 167 
#define  T_OPEN_TAG 166 
#define  T_OPEN_TAG_WITH_ECHO 165 
#define  T_OR_EQUAL 164 
#define  T_PAAMAYIM_NEKUDOTAYIM 163 
#define  T_PLUS_EQUAL 162 
#define  T_POW 161 
#define  T_POW_EQUAL 160 
#define  T_PRINT 159 
#define  T_PRIVATE 158 
#define  T_PROTECTED 157 
#define  T_PUBLIC 156 
#define  T_REQUIRE 155 
#define  T_REQUIRE_ONCE 154 
#define  T_RETURN 153 
#define  T_SL 152 
#define  T_SL_EQUAL 151 
#define  T_SPACESHIP 150 
#define  T_SR 149 
#define  T_SR_EQUAL 148 
#define  T_START_HEREDOC 147 
#define  T_STATIC 146 
#define  T_STRING 145 
#define  T_STRING_CAST 144 
#define  T_STRING_VARNAME 143 
#define  T_SWITCH 142 
#define  T_THROW 141 
#define  T_TRAIT 140 
#define  T_TRAIT_C 139 
#define  T_TRY 138 
#define  T_UNSET 137 
#define  T_UNSET_CAST 136 
#define  T_USE 135 
#define  T_VAR 134 
#define  T_VARIABLE 133 
#define  T_WHILE 132 
#define  T_WHITESPACE 131 
#define  T_XOR_EQUAL 130 
#define  T_YIELD 129 
#define  T_YIELD_FROM 128 

char *get_token_type_name(int token_type)
{
	switch (token_type) {

		case T_INCLUDE: return "T_INCLUDE";
		case T_INCLUDE_ONCE: return "T_INCLUDE_ONCE";
		case T_REQUIRE: return "T_REQUIRE";
		case T_REQUIRE_ONCE: return "T_REQUIRE_ONCE";
		case T_LOGICAL_OR: return "T_LOGICAL_OR";
		case T_LOGICAL_XOR: return "T_LOGICAL_XOR";
		case T_LOGICAL_AND: return "T_LOGICAL_AND";
		case T_PRINT: return "T_PRINT";
		case T_YIELD: return "T_YIELD";
		case T_DOUBLE_ARROW: return "T_DOUBLE_ARROW";
		case T_YIELD_FROM: return "T_YIELD_FROM";
		case T_PLUS_EQUAL: return "T_PLUS_EQUAL";
		case T_MINUS_EQUAL: return "T_MINUS_EQUAL";
		case T_MUL_EQUAL: return "T_MUL_EQUAL";
		case T_DIV_EQUAL: return "T_DIV_EQUAL";
		case T_CONCAT_EQUAL: return "T_CONCAT_EQUAL";
		case T_MOD_EQUAL: return "T_MOD_EQUAL";
		case T_AND_EQUAL: return "T_AND_EQUAL";
		case T_OR_EQUAL: return "T_OR_EQUAL";
		case T_XOR_EQUAL: return "T_XOR_EQUAL";
		case T_SL_EQUAL: return "T_SL_EQUAL";
		case T_SR_EQUAL: return "T_SR_EQUAL";
		case T_POW_EQUAL: return "T_POW_EQUAL";
		case T_COALESCE_EQUAL: return "T_COALESCE_EQUAL";
		case T_COALESCE: return "T_COALESCE";
		case T_BOOLEAN_OR: return "T_BOOLEAN_OR";
		case T_BOOLEAN_AND: return "T_BOOLEAN_AND";
		case T_IS_EQUAL: return "T_IS_EQUAL";
		case T_IS_NOT_EQUAL: return "T_IS_NOT_EQUAL";
		case T_IS_IDENTICAL: return "T_IS_IDENTICAL";
		case T_IS_NOT_IDENTICAL: return "T_IS_NOT_IDENTICAL";
		case T_SPACESHIP: return "T_SPACESHIP";
		case T_IS_SMALLER_OR_EQUAL: return "T_IS_SMALLER_OR_EQUAL";
		case T_IS_GREATER_OR_EQUAL: return "T_IS_GREATER_OR_EQUAL";
		case T_SL: return "T_SL";
		case T_SR: return "T_SR";
		case T_INSTANCEOF: return "T_INSTANCEOF";
		case T_INC: return "T_INC";
		case T_DEC: return "T_DEC";
		case T_INT_CAST: return "T_INT_CAST";
		case T_DOUBLE_CAST: return "T_DOUBLE_CAST";
		case T_STRING_CAST: return "T_STRING_CAST";
		case T_ARRAY_CAST: return "T_ARRAY_CAST";
		case T_OBJECT_CAST: return "T_OBJECT_CAST";
		case T_BOOL_CAST: return "T_BOOL_CAST";
		case T_UNSET_CAST: return "T_UNSET_CAST";
		case T_POW: return "T_POW";
		case T_NEW: return "T_NEW";
		case T_CLONE: return "T_CLONE";
		case T_ELSEIF: return "T_ELSEIF";
		case T_ELSE: return "T_ELSE";
		case T_LNUMBER: return "T_LNUMBER";
		case T_DNUMBER: return "T_DNUMBER";
		case T_STRING: return "T_STRING";
		case T_VARIABLE: return "T_VARIABLE";
		case T_INLINE_HTML: return "T_INLINE_HTML";
		case T_ENCAPSED_AND_WHITESPACE: return "T_ENCAPSED_AND_WHITESPACE";
		case T_CONSTANT_ENCAPSED_STRING: return "T_CONSTANT_ENCAPSED_STRING";
		case T_STRING_VARNAME: return "T_STRING_VARNAME";
		case T_NUM_STRING: return "T_NUM_STRING";
		case T_EVAL: return "T_EVAL";
		case T_EXIT: return "T_EXIT";
		case T_IF: return "T_IF";
		case T_ENDIF: return "T_ENDIF";
		case T_ECHO: return "T_ECHO";
		case T_DO: return "T_DO";
		case T_WHILE: return "T_WHILE";
		case T_ENDWHILE: return "T_ENDWHILE";
		case T_FOR: return "T_FOR";
		case T_ENDFOR: return "T_ENDFOR";
		case T_FOREACH: return "T_FOREACH";
		case T_ENDFOREACH: return "T_ENDFOREACH";
		case T_DECLARE: return "T_DECLARE";
		case T_ENDDECLARE: return "T_ENDDECLARE";
		case T_AS: return "T_AS";
		case T_SWITCH: return "T_SWITCH";
		case T_ENDSWITCH: return "T_ENDSWITCH";
		case T_CASE: return "T_CASE";
		case T_DEFAULT: return "T_DEFAULT";
		case T_BREAK: return "T_BREAK";
		case T_CONTINUE: return "T_CONTINUE";
		case T_GOTO: return "T_GOTO";
		case T_FUNCTION: return "T_FUNCTION";
		case T_CONST: return "T_CONST";
		case T_RETURN: return "T_RETURN";
		case T_TRY: return "T_TRY";
		case T_CATCH: return "T_CATCH";
		case T_FINALLY: return "T_FINALLY";
		case T_THROW: return "T_THROW";
		case T_USE: return "T_USE";
		case T_INSTEADOF: return "T_INSTEADOF";
		case T_GLOBAL: return "T_GLOBAL";
		case T_STATIC: return "T_STATIC";
		case T_ABSTRACT: return "T_ABSTRACT";
		case T_FINAL: return "T_FINAL";
		case T_PRIVATE: return "T_PRIVATE";
		case T_PROTECTED: return "T_PROTECTED";
		case T_PUBLIC: return "T_PUBLIC";
		case T_VAR: return "T_VAR";
		case T_UNSET: return "T_UNSET";
		case T_ISSET: return "T_ISSET";
		case T_EMPTY: return "T_EMPTY";
		case T_HALT_COMPILER: return "T_HALT_COMPILER";
		case T_CLASS: return "T_CLASS";
		case T_TRAIT: return "T_TRAIT";
		case T_INTERFACE: return "T_INTERFACE";
		case T_EXTENDS: return "T_EXTENDS";
		case T_IMPLEMENTS: return "T_IMPLEMENTS";
		case T_OBJECT_OPERATOR: return "T_OBJECT_OPERATOR";
		case T_LIST: return "T_LIST";
		case T_ARRAY: return "T_ARRAY";
		case T_CALLABLE: return "T_CALLABLE";
		case T_LINE: return "T_LINE";
		case T_FILE: return "T_FILE";
		case T_DIR: return "T_DIR";
		case T_CLASS_C: return "T_CLASS_C";
		case T_TRAIT_C: return "T_TRAIT_C";
		case T_METHOD_C: return "T_METHOD_C";
		case T_FUNC_C: return "T_FUNC_C";
		case T_COMMENT: return "T_COMMENT";
		case T_DOC_COMMENT: return "T_DOC_COMMENT";
		case T_OPEN_TAG: return "T_OPEN_TAG";
		case T_OPEN_TAG_WITH_ECHO: return "T_OPEN_TAG_WITH_ECHO";
		case T_CLOSE_TAG: return "T_CLOSE_TAG";
		case T_WHITESPACE: return "T_WHITESPACE";
		case T_START_HEREDOC: return "T_START_HEREDOC";
		case T_END_HEREDOC: return "T_END_HEREDOC";
		case T_DOLLAR_OPEN_CURLY_BRACES: return "T_DOLLAR_OPEN_CURLY_BRACES";
		case T_CURLY_OPEN: return "T_CURLY_OPEN";
		case T_PAAMAYIM_NEKUDOTAYIM: return "T_DOUBLE_COLON";
		case T_NAMESPACE: return "T_NAMESPACE";
		case T_NS_C: return "T_NS_C";
		case T_NS_SEPARATOR: return "T_NS_SEPARATOR";
		case T_ELLIPSIS: return "T_ELLIPSIS";

	}
	return "UNKNOWN";
}