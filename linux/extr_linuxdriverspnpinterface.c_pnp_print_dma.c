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
struct pnp_dma {int map; int flags; } ;
typedef  int /*<<< orphan*/  pnp_info_buffer_t ;

/* Variables and functions */
#define  IORESOURCE_DMA_8AND16BIT 132 
#define  IORESOURCE_DMA_8BIT 131 
 int IORESOURCE_DMA_BYTE ; 
 int IORESOURCE_DMA_MASTER ; 
 int IORESOURCE_DMA_SPEED_MASK ; 
#define  IORESOURCE_DMA_TYPEA 130 
#define  IORESOURCE_DMA_TYPEB 129 
#define  IORESOURCE_DMA_TYPEF 128 
 int IORESOURCE_DMA_TYPE_MASK ; 
 int IORESOURCE_DMA_WORD ; 
 int /*<<< orphan*/  pnp_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void pnp_print_dma(pnp_info_buffer_t * buffer, char *space,
			  struct pnp_dma *dma)
{
	int first = 1, i;
	char *s;

	pnp_printf(buffer, "%sdma ", space);
	for (i = 0; i < 8; i++)
		if (dma->map & (1 << i)) {
			if (!first) {
				pnp_printf(buffer, ",");
			} else {
				first = 0;
			}
			pnp_printf(buffer, "%i", i);
		}
	if (!dma->map)
		pnp_printf(buffer, "<none>");
	switch (dma->flags & IORESOURCE_DMA_TYPE_MASK) {
	case IORESOURCE_DMA_8BIT:
		s = "8-bit";
		break;
	case IORESOURCE_DMA_8AND16BIT:
		s = "8-bit&16-bit";
		break;
	default:
		s = "16-bit";
	}
	pnp_printf(buffer, " %s", s);
	if (dma->flags & IORESOURCE_DMA_MASTER)
		pnp_printf(buffer, " master");
	if (dma->flags & IORESOURCE_DMA_BYTE)
		pnp_printf(buffer, " byte-count");
	if (dma->flags & IORESOURCE_DMA_WORD)
		pnp_printf(buffer, " word-count");
	switch (dma->flags & IORESOURCE_DMA_SPEED_MASK) {
	case IORESOURCE_DMA_TYPEA:
		s = "type-A";
		break;
	case IORESOURCE_DMA_TYPEB:
		s = "type-B";
		break;
	case IORESOURCE_DMA_TYPEF:
		s = "type-F";
		break;
	default:
		s = "compatible";
		break;
	}
	pnp_printf(buffer, " %s\n", s);
}