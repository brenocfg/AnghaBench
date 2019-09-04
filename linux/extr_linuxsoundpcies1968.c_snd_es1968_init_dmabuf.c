#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int addr; int bytes; int /*<<< orphan*/  area; TYPE_1__ dev; } ;
struct esm_memory {int empty; int /*<<< orphan*/  list; TYPE_3__ buf; } ;
struct es1968 {int /*<<< orphan*/  buf_list; TYPE_3__ dma; TYPE_2__* card; int /*<<< orphan*/  total_bufsize; int /*<<< orphan*/  pci; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ESM_MEM_ALIGN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct esm_memory* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int snd_dma_alloc_pages_fallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1968_free_dmabuf (struct es1968*) ; 

__attribute__((used)) static int
snd_es1968_init_dmabuf(struct es1968 *chip)
{
	int err;
	struct esm_memory *chunk;

	chip->dma.dev.type = SNDRV_DMA_TYPE_DEV;
	chip->dma.dev.dev = snd_dma_pci_data(chip->pci);
	err = snd_dma_alloc_pages_fallback(SNDRV_DMA_TYPE_DEV,
					   snd_dma_pci_data(chip->pci),
					   chip->total_bufsize, &chip->dma);
	if (err < 0 || ! chip->dma.area) {
		dev_err(chip->card->dev,
			"can't allocate dma pages for size %d\n",
			   chip->total_bufsize);
		return -ENOMEM;
	}
	if ((chip->dma.addr + chip->dma.bytes - 1) & ~((1 << 28) - 1)) {
		snd_dma_free_pages(&chip->dma);
		dev_err(chip->card->dev, "DMA buffer beyond 256MB.\n");
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&chip->buf_list);
	/* allocate an empty chunk */
	chunk = kmalloc(sizeof(*chunk), GFP_KERNEL);
	if (chunk == NULL) {
		snd_es1968_free_dmabuf(chip);
		return -ENOMEM;
	}
	memset(chip->dma.area, 0, ESM_MEM_ALIGN);
	chunk->buf = chip->dma;
	chunk->buf.area += ESM_MEM_ALIGN;
	chunk->buf.addr += ESM_MEM_ALIGN;
	chunk->buf.bytes -= ESM_MEM_ALIGN;
	chunk->empty = 1;
	list_add(&chunk->list, &chip->buf_list);

	return 0;
}