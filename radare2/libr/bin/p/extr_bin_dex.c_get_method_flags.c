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
typedef  int ut64 ;

/* Variables and functions */
 int R_BIN_METH_ABSTRACT ; 
 int R_BIN_METH_BRIDGE ; 
 int R_BIN_METH_CONSTRUCTOR ; 
 int R_BIN_METH_DECLARED_SYNCHRONIZED ; 
 int R_BIN_METH_FINAL ; 
 int R_BIN_METH_MIRANDA ; 
 int R_BIN_METH_NATIVE ; 
 int R_BIN_METH_PRIVATE ; 
 int R_BIN_METH_PROTECTED ; 
 int R_BIN_METH_PUBLIC ; 
 int R_BIN_METH_STATIC ; 
 int R_BIN_METH_STRICT ; 
 int R_BIN_METH_SYNCHRONIZED ; 
 int R_BIN_METH_SYNTHETIC ; 
 int R_BIN_METH_VARARGS ; 
 int R_DEX_METH_ABSTRACT ; 
 int R_DEX_METH_BRIDGE ; 
 int R_DEX_METH_CONSTRUCTOR ; 
 int R_DEX_METH_DECLARED_SYNCHRONIZED ; 
 int R_DEX_METH_FINAL ; 
 int R_DEX_METH_MIRANDA ; 
 int R_DEX_METH_NATIVE ; 
 int R_DEX_METH_PRIVATE ; 
 int R_DEX_METH_PROTECTED ; 
 int R_DEX_METH_PUBLIC ; 
 int R_DEX_METH_STATIC ; 
 int R_DEX_METH_STRICT ; 
 int R_DEX_METH_SYNCHRONIZED ; 
 int R_DEX_METH_SYNTHETIC ; 
 int R_DEX_METH_VARARGS ; 

__attribute__((used)) static ut64 get_method_flags(ut64 MA) {
	ut64 flags = 0;
	if (MA & R_DEX_METH_PUBLIC) {
		flags |= R_BIN_METH_PUBLIC;
	}
	if (MA & R_DEX_METH_PRIVATE) {
		flags |= R_BIN_METH_PRIVATE;
	}
	if (MA & R_DEX_METH_PROTECTED) {
		flags |= R_BIN_METH_PROTECTED;
	}
	if (MA & R_DEX_METH_STATIC) {
		flags |= R_BIN_METH_STATIC;
	}
	if (MA & R_DEX_METH_FINAL) {
		flags |= R_BIN_METH_FINAL;
	}
	if (MA & R_DEX_METH_SYNCHRONIZED) {
		flags |= R_BIN_METH_SYNCHRONIZED;
	}
	if (MA & R_DEX_METH_BRIDGE) {
		flags |= R_BIN_METH_BRIDGE;
	}
	if (MA & R_DEX_METH_VARARGS) {
		flags |= R_BIN_METH_VARARGS;
	}
	if (MA & R_DEX_METH_NATIVE) {
		flags |= R_BIN_METH_NATIVE;
	}
	if (MA & R_DEX_METH_ABSTRACT) {
		flags |= R_BIN_METH_ABSTRACT;
	}
	if (MA & R_DEX_METH_STRICT) {
		flags |= R_BIN_METH_STRICT;
	}
	if (MA & R_DEX_METH_SYNTHETIC) {
		flags |= R_BIN_METH_SYNTHETIC;
	}
	if (MA & R_DEX_METH_MIRANDA) {
		flags |= R_BIN_METH_MIRANDA;
	}
	if (MA & R_DEX_METH_CONSTRUCTOR) {
		flags |= R_BIN_METH_CONSTRUCTOR;
	}
	if (MA & R_DEX_METH_DECLARED_SYNCHRONIZED) {
		flags |= R_BIN_METH_DECLARED_SYNCHRONIZED;
	}
	return flags;
}