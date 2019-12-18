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
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_MIB_FUNC_CAPTURE ; 
 int ar8xxx_mib_op (struct ar8xxx_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8xxx_mib_capture(struct ar8xxx_priv *priv)
{
	return ar8xxx_mib_op(priv, AR8216_MIB_FUNC_CAPTURE);
}