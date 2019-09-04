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
struct sci_port_params {int dummy; } ;
struct plat_sci_port {size_t regtype; int type; } ;

/* Variables and functions */
#define  PORT_HSCIF 133 
#define  PORT_IRDA 132 
#define  PORT_SCI 131 
#define  PORT_SCIF 130 
#define  PORT_SCIFA 129 
#define  PORT_SCIFB 128 
 unsigned int SCIx_HSCIF_REGTYPE ; 
 unsigned int SCIx_IRDA_REGTYPE ; 
 size_t SCIx_PROBE_REGTYPE ; 
 unsigned int SCIx_SCIFA_REGTYPE ; 
 unsigned int SCIx_SCIFB_REGTYPE ; 
 unsigned int SCIx_SCI_REGTYPE ; 
 unsigned int SCIx_SH4_SCIF_REGTYPE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct sci_port_params const* sci_port_params ; 

__attribute__((used)) static const struct sci_port_params *
sci_probe_regmap(const struct plat_sci_port *cfg)
{
	unsigned int regtype;

	if (cfg->regtype != SCIx_PROBE_REGTYPE)
		return &sci_port_params[cfg->regtype];

	switch (cfg->type) {
	case PORT_SCI:
		regtype = SCIx_SCI_REGTYPE;
		break;
	case PORT_IRDA:
		regtype = SCIx_IRDA_REGTYPE;
		break;
	case PORT_SCIFA:
		regtype = SCIx_SCIFA_REGTYPE;
		break;
	case PORT_SCIFB:
		regtype = SCIx_SCIFB_REGTYPE;
		break;
	case PORT_SCIF:
		/*
		 * The SH-4 is a bit of a misnomer here, although that's
		 * where this particular port layout originated. This
		 * configuration (or some slight variation thereof)
		 * remains the dominant model for all SCIFs.
		 */
		regtype = SCIx_SH4_SCIF_REGTYPE;
		break;
	case PORT_HSCIF:
		regtype = SCIx_HSCIF_REGTYPE;
		break;
	default:
		pr_err("Can't probe register map for given port\n");
		return NULL;
	}

	return &sci_port_params[regtype];
}